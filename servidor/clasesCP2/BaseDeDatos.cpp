/*
 * BasedeDatos.cpp
 *
 *  Created on: 19 de oct. de 2015
 *      Author: mafv
 */

#include "BaseDeDatos.h"

BasedeDatos* BasedeDatos::unicaInstancia = NULL;

BasedeDatos * BasedeDatos::obteberInstancia(){

	if( unicaInstancia == NULL ){

		unicaInstancia = new BasedeDatos();
		atexit(&destruirInstancia);

	}
	return unicaInstancia;

}

bool BasedeDatos::guardar(const int TIPO,const string &clave,const string &valor){

	this->mtx.lock();

	WriteBatch batch;
	batch.Put(handles[TIPO], Slice(clave), Slice(valor));

	estado = db->Write(WriteOptions(), &batch);
	this->mtx.unlock();

	return estado.ok();

}

const string BasedeDatos::leer(const int TIPO,const string &clave){

	string datosExistente;
	
	estado = db->Get(ReadOptions(), handles[TIPO], Slice(clave), &datosExistente);

	return datosExistente;

}

bool BasedeDatos::eliminar(const int TIPO,const string &clave){

	this->mtx.lock();

	WriteBatch batch;
	batch.Delete(handles[TIPO], Slice(clave));
	estado = db->Write(WriteOptions(), &batch);

	this->mtx.unlock();

}

BasedeDatos::~BasedeDatos() {

	for (auto handle : handles) {
		delete handle;
	}
	delete db;

}

//METODOS PRIVADOS

BasedeDatos::BasedeDatos() {

	dirPath = "testdb/";
	Options opciones;
	opciones.create_if_missing = true;
	opciones.error_if_exists = true;
	estado = DB::Open(opciones,dirPath, &db);
	if(estado.ok())
		this->inicializarColumnas();
	
	this->cargarColumnas();

}
void BasedeDatos::destruirInstancia(){
	if(unicaInstancia != NULL)
		delete unicaInstancia;
}

void BasedeDatos::inicializarColumnas(){

	ColumnFamilyHandle* usuarios;
	ColumnFamilyHandle* archivos;
	ColumnFamilyHandle* etiquetas;
	ColumnFamilyHandle* nombre;
	ColumnFamilyHandle* extension;
	ColumnFamilyHandle* propietario;

	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"USUARIOS", &usuarios);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ARCHIVOS", &archivos);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ETIQUETAS", &etiquetas);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"NOMBRE", &nombre);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"EXTENSION", &extension);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"PROPIETARIO", &propietario);

	delete usuarios;
	delete archivos;
	delete etiquetas;
	delete nombre;
	delete extension;
	delete propietario;

	delete db;

}

void BasedeDatos::cargarColumnas(){

	vector<ColumnFamilyDescriptor> column_families;

	column_families.push_back(ColumnFamilyDescriptor(kDefaultColumnFamilyName, ColumnFamilyOptions()));

	column_families.push_back(ColumnFamilyDescriptor("USUARIOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("ARCHIVOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("ETIQUETAS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("NOMBRE", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("EXTENSION", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("PROPIETARIO", ColumnFamilyOptions()));

	estado = DB::Open(DBOptions(), dirPath, column_families, &handles, &db);

}