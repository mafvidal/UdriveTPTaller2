#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <iostream>
#include "rocksdb/db.h"
#include <assert.h>

using namespace std;
using namespace rocksdb;

class BaseDeDatos {
private:
	DB* db;
	Status estado;
public:
	BaseDeDatos(string directorio);
	BaseDeDatos();
	//Agrega un usuario nuevo a la base de datos
	//El usuario no debe existir
	bool setUsuario(string nombreUsuario,string clave);
	bool existeUsuario(string nombreUsuario);
	//Devuelve si la clave es la del usuario
	//El usuario debe existir
	bool esLaClaveCorrecta(string nombreUsuario,string clave);
	~BaseDeDatos();
};

#endif /* BASEDEDATOS_H_ */
