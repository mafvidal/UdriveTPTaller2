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


bool BaseDeDatos::setUsuario(string nombreUsuario,string clave){

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(clave));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::existeUsuario(string nombreUsuario){

	string value;
	estado = db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &value);
	return estado.ok();

}


bool BaseDeDatos::esLaClaveCorrecta(string nombreUsuario,string clave){

	string claveReal;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &claveReal);

	return (clave == claveReal);

}
string BaseDeDatos::getDatosUsuario(string nombreUsuario){

	string datos;

	db->Get(ReadOptions(), handles[DATOSUSARIOS], Slice(nombreUsuario), &datos);

	return datos;

}

bool BaseDeDatos::setDatosUsuario(string nombreUsuario, string datosUsuario){

	WriteBatch batch;
	batch.Put(handles[DATOSUSARIOS], Slice(nombreUsuario), Slice(datosUsuario));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::agregarArchivo(string nombreUsuario, string archivo){
	
	string listaDeArchivos;

	estado=db->Get(ReadOptions(), handles[ARCHIVOSUSARIOS], Slice(nombreUsuario), &listaDeArchivos);
	//El usuario no tiene archivos en la base
	if(!estado.ok()){
		WriteBatch batch;
		batch.Put(handles[ARCHIVOSUSARIOS], Slice(nombreUsuario), Slice(archivo));
		estado = db->Write(WriteOptions(), &batch);
	}else{
		listaDeArchivos=listaDeArchivos+"-"+archivo;
		WriteBatch batch;
		batch.Put(handles[ARCHIVOSUSARIOS], Slice(nombreUsuario), Slice(listaDeArchivos));
		estado = db->Write(WriteOptions(), &batch);
	}		

}

list<Archivo> BaseDeDatos::getArchivos(string nombreUsuario){

	string listaDeArchivos;

	estado=db->Get(ReadOptions(), handles[ARCHIVOSUSARIOS], Slice(nombreUsuario), &listaDeArchivos);

	if(!estado.ok()){
		list<Archivo> archivos;
		return archivos;
	}else{
		return this->parsearArchivos(listaDeArchivos);
	}

}

BaseDeDatos::~BaseDeDatos() {

	for (auto handle : handles) {
		delete handle;
	}
	delete db;

}

void BaseDeDatos::inicializarColumnas(){

	ColumnFamilyHandle* usuarios;
	ColumnFamilyHandle* datosUsuarios;
	ColumnFamilyHandle* archivosUsuarios;

	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"USUARIOS", &usuarios);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"DATOSUSARIOS", &datosUsuarios);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ARCHIVOSUSARIOS", &archivosUsuarios);

	delete usuarios;
	delete datosUsuarios;
	delete archivosUsuarios;

	delete db;

}

void BaseDeDatos::cargarColumnas(){

	vector<ColumnFamilyDescriptor> column_families;

	column_families.push_back(ColumnFamilyDescriptor(
			kDefaultColumnFamilyName, ColumnFamilyOptions()));

	column_families.push_back(ColumnFamilyDescriptor(
			"USUARIOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor(
			"DATOSUSARIOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor(
			"ARCHIVOSUSARIOS", ColumnFamilyOptions()));

	estado = DB::Open(DBOptions(), dirPath, column_families, &handles, &db);

}

list<Archivo> BaseDeDatos::parsearArchivos(string listaDeArchivos){

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

}
