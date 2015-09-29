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


bool BaseDeDatos::agregarUsuario(string nombreUsuario,string clave,string metadatosJson,float cuota){

	DatosDeUsuario dato;

	string datosUsuarios;

	datosUsuarios = dato.obtenerDatosDeUsuarios(metadatosJson,clave,cuota);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datosUsuarios));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::existeUsuario(string nombreUsuario){

	string value;
	estado = db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &value);
	return estado.ok();

}


bool BaseDeDatos::esLaClaveCorrecta(string nombreUsuario,string clave){

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	return (clave == datos.clave(datosUsuario));

}
string BaseDeDatos::getMetaDatosUsuario(string nombreUsuario){

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	return datos.obtenerMetadatosDelUsuario(datosUsuario);

}

bool BaseDeDatos::setDatosUsuario(string nombreUsuario, string metaDatosUsuario){

	string datoUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datoUsuario);

	DatosDeUsuario datos;

	datoUsuario = datos.modificarDatosDeUsuarios(datoUsuario,metaDatosUsuario);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datoUsuario));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::agregarArchivo(string nombreUsuario,string metadatos,float espacio){

	//Guardo archivo
	DatosDeArchivos datosArchivo;
	string datosArchivoAGuardar;

	datosArchivoAGuardar = datosArchivo.obtenerDatos(metadatos);
	
	unsigned int hash = this->obtenerHash(datosArchivo.getNombreCompleto(datosArchivoAGuardar));
	string hashString = this->convertirAString(hash);

	string archivoExistente;

	estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);
	while(estado.ok()){
		hash++;
		hashString = this->convertirAString(hash);
		estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);
	}

	WriteBatch batchArchivos;
	batchArchivos.Put(handles[ARCHIVOS], Slice(hashString), Slice(datosArchivoAGuardar));
	estado = db->Write(WriteOptions(), &batchArchivos);

	//Guardo el archivo en el usuario

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	WriteBatch batch;

	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datos.agregarArchivoNuevo(datosUsuario,hashString,espacio)));
	estado = db->Write(WriteOptions(), &batch);

}

list<string> BaseDeDatos::getArchivos(string nombreUsuario){

	list<string> listaDeArchivos;
	list<string> listaDeMetadatos;

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	listaDeArchivos = datos.obtenerArchivos(datosUsuario);

	for(list<string>::iterator it = listaDeArchivos.begin(); it != listaDeArchivos.end(); it++){

		DatosDeArchivos datosArchivo;
		string datosDelArchivo;

		db->Get(ReadOptions(), handles[ARCHIVOS], Slice((*it)), &datosDelArchivo);

		listaDeMetadatos.push_back(datosArchivo.obtenerMetadatos(datosDelArchivo));

	}

	return listaDeMetadatos;

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

	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"USUARIOS", &usuarios);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ARCHIVOS", &archivos);

	delete usuarios;
	delete archivos;

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

	estado = DB::Open(DBOptions(), dirPath, column_families, &handles, &db);

}
