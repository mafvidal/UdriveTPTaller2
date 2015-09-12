#include "BaseDeDatos.h"

BaseDeDatos::BaseDeDatos(string directorio) {

	cout<<directorio<<endl;
	Options opciones;
	opciones.create_if_missing = true;
	estado = DB::Open(opciones,directorio, &db);
	//assert(estado.ok());

}

BaseDeDatos::BaseDeDatos() {
	
	Options opciones;
	opciones.create_if_missing = true;
	estado = DB::Open(opciones, "/tmp/mydb_rocks", &db);
	assert(estado.ok());

}

bool BaseDeDatos::setUsuario(string nombreUsuario,string clave){

	estado = this->db->Put(WriteOptions(), nombreUsuario, clave);

	return estado.ok();

}

bool BaseDeDatos::existeUsuario(string nombreUsuario){

	string clave;
	estado = db->Get(ReadOptions(), nombreUsuario, &clave);

	return estado.ok();

}

bool BaseDeDatos::esLaClaveCorrecta(string nombreUsuario,string clave){

	string claveReal;
	estado = db->Get(ReadOptions(), nombreUsuario, &claveReal);

	return (clave == claveReal);

}

BaseDeDatos::~BaseDeDatos() {

	delete db;

}
