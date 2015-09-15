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

BaseDeDatos::~BaseDeDatos() {

	for (auto handle : handles) {
		delete handle;
	}
	delete db;

}

void BaseDeDatos::inicializarColumnas(){

	ColumnFamilyHandle* usuarios;
	ColumnFamilyHandle* datosUsuarios;

	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"USUARIOS", &usuarios);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"DATOSUSARIOS", &datosUsuarios);

	delete usuarios;
	delete datosUsuarios;

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

	estado = DB::Open(DBOptions(), dirPath, column_families, &handles, &db);

}
