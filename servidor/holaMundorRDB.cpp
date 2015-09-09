#include <iostream>
#include <string>
#include <assert.h>
#include "bibliotecas/rocksdb/include/rocksdb/db.h"
#include "bibliotecas/rocksdb/include/rocksdb/table.h"

using namespace std;
using namespace rocksdb;

int main(int argc, char** argv) {

	/*CREACION DE LA BASE DE DATOS*/
	DB* db; //Base de datos
	Options options;
	options.create_if_missing = true;
	//Abre la base de datos
	Status status = DB::Open(options, "/tmp/mydb_rocks", &db);
	if (!status.ok())
		cerr << status.ToString() << endl;

	/*AGREGAR DATOS A LA BASE DE DATOS*/
	string key1="1";
	string value="Hola";
	string value2;
	status = db->Put(rocksdb::WriteOptions(), key1, value); //Agrego en la base de datos el valor 									  (1,Hola)
	if (status.ok()) 
		status = db->Get(rocksdb::ReadOptions(), key1, &value2); //guardo en value2 = "Hola"
	
	assert(value==value2);

	/*ELIMINACION DE LA BASE DE DATOS*/
	delete db;

	return 0;
}
