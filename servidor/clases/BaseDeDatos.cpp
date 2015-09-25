#include "BaseDeDatos.h"

BaseDeDatos::BaseDeDatos(string directorio) {

	dirPath = directorio;
	Options opciones;
	opciones.create_if_missing = true;
	opciones.error_if_exists = true;
	estado = DB::Open(opciones,dirPath, &db);
	if(estado.ok())
		this->inicializarColumnas();
	
	this->cargarColumnas();

}


bool BaseDeDatos::setUsuario(string nombreUsuario,string clave,float cuota){

	DatosDeUsuario dato(clave,cuota);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(dato.getDatos()));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::existeUsuario(string nombreUsuario){

	string value;
	estado = db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &value);
	return estado.ok();

}


bool BaseDeDatos::esLaClaveCorrecta(string nombreUsuario,string clave){

	string datos;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datos);

	DatosDeUsuario datosDeUsuario(datos);

	return (clave == datosDeUsuario.getClave());

}
string BaseDeDatos::getDatosUsuario(string nombreUsuario){

	string datos;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datos);

	DatosDeUsuario datosDeUsuario(datos);

	return datosDeUsuario.getDatosDelUsuario();

}

bool BaseDeDatos::setDatosUsuario(string nombreUsuario, string datosUsuario){

	string datos;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datos);

	DatosDeUsuario datosDeUsuario(datos);

	datosDeUsuario.cargarDatosDelUsuario(datosUsuario);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datosDeUsuario.getDatos()));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::agregarArchivo(string nombreUsuario,string metadatos,float espacio){

	string datos;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datos);

	DatosDeUsuario datosDeUsuario(datos);

	DatosDeArchivos datosDeArchivos(metadatos);

	unsigned int hash = this->obtenerHash(datosDeArchivos.getNombreCompleto());
	string hashString = this->convertirAString(hash);

	string nombreArchivo;

	estado = db->Get(ReadOptions(), handles[ARCHIVOSNOMBRES], Slice(hashString), &nombreArchivo);
	while(estado.ok()){
		hash++;
		hashString = this->convertirAString(hash);
		estado = db->Get(ReadOptions(), handles[ARCHIVOSNOMBRES], Slice(hashString), &nombreArchivo);
	}

	datosDeUsuario.setArchivo(hashString,espacio);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datosDeUsuario.getDatos()));
	estado = db->Write(WriteOptions(), &batch);
	
	WriteBatch batchArchivoNombre;
	batchArchivoNombre.Put(handles[ARCHIVOSNOMBRES], Slice(hashString), Slice(datosDeArchivos.getNombreCompleto()));
	estado = db->Write(WriteOptions(), &batchArchivoNombre);


	WriteBatch batchArchivos;
	batchArchivos.Put(handles[ARCHIVOS], Slice(hashString), Slice(datosDeArchivos.getDatos()));
	estado = db->Write(WriteOptions(), &batchArchivos);
	

}

list<string> BaseDeDatos::getArchivos(string nombreUsuario){

	list<string> listaDeArchivos;

	string datos;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datos);

	DatosDeUsuario datosDeUsuario(datos);

	//cout<<datos<<endl;

	list<string> hashDeArchivos = datosDeUsuario.getArchivos();

	for(list<string>::iterator it = hashDeArchivos.begin(); it != hashDeArchivos.end(); it++){
		DatosDeArchivos datosDeArchivos;
		string datosArchivo;
		//cout<<(*it)<<endl;
		db->Get(ReadOptions(), handles[ARCHIVOS], Slice((*it)), &datosArchivo);
		//cout<<datosArchivo<<endl;
		datosDeArchivos.setDatos(datosArchivo);
		//cout<<datosDeArchivos.getMetadatosDatos()<<endl;
		listaDeArchivos.push_back(datosDeArchivos.getMetadatosDatos());
	}

	return listaDeArchivos;

}

BaseDeDatos::~BaseDeDatos() {

	for (auto handle : handles) {
		delete handle;
	}
	delete db;

}

unsigned int BaseDeDatos::obtenerHash(string archivo){

	unsigned int hash = 0;

	for(int i=0; i<archivo.size(); ++i)
	{
		hash += archivo[i];
		hash += (hash << 10);
 		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;

}

string BaseDeDatos::convertirAString(unsigned int hash){

	string hashString;
	ostringstream convertir;
	convertir << hash;
	hashString = convertir.str();

	return hashString;


}
void BaseDeDatos::inicializarColumnas(){

	ColumnFamilyHandle* usuarios;
	ColumnFamilyHandle* archivos;
	ColumnFamilyHandle* archivosNombres;

	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"USUARIOS", &usuarios);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ARCHIVOS", &archivos);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ARCHIVOSNOMBRES", &archivosNombres);

	delete usuarios;
	delete archivos;
	delete archivosNombres;

	delete db;

}

void BaseDeDatos::cargarColumnas(){

	vector<ColumnFamilyDescriptor> column_families;

	column_families.push_back(ColumnFamilyDescriptor(
			kDefaultColumnFamilyName, ColumnFamilyOptions()));

	column_families.push_back(ColumnFamilyDescriptor(
			"USUARIOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor(
			"ARCHIVOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor(
			"ARCHIVOSNOMBRES", ColumnFamilyOptions()));

	estado = DB::Open(DBOptions(), dirPath, column_families, &handles, &db);

}

/*list<Archivo> BaseDeDatos::parsearArchivos(string listaDeArchivos){

	list<string> lista;
	size_t finArchivo = listaDeArchivos.find("-");
	size_t posicionInicial=0;

	for(int i=0;finArchivo!=string::npos;){
		lista.push_back(listaDeArchivos.substr(i,finArchivo-posicionInicial));
		i=finArchivo+1;
		posicionInicial=finArchivo+1;
		finArchivo = listaDeArchivos.find("-",posicionInicial);
	}

	lista.push_back(listaDeArchivos.substr(posicionInicial,listaDeArchivos.size()-posicionInicial));

	list<Archivo> archivos;

	for (std::list<string>::iterator it = lista.begin(); it != lista.end(); it++){
		Archivo archivo;
		size_t posFin = (*it).find_last_of('/');
		size_t largo = (*it).size();
		archivo.nombre=(*it).substr(posFin+1,largo-posFin);
		archivo.directorio=(*it).substr(0,posFin+1);
		archivos.push_back(archivo);
	}

	return archivos;

}*/
