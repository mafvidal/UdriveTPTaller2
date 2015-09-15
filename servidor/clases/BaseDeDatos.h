#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <iostream>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include <vector>
#include <assert.h>

using namespace std;
using namespace rocksdb;

class BaseDeDatos {
private:
	const int USARIOS=1;
	DB* db;
	Status estado;
	string dirPath;
	vector<ColumnFamilyHandle*> handles;

public:
	BaseDeDatos(string directorio);

	//Agrega un usuario nuevo a la base de datos
	//El usuario no debe existir
	bool setUsuario(string nombreUsuario,string clave);
	bool existeUsuario(string nombreUsuario);
	//Devuelve si la clave es la del usuario
	//El usuario debe existir
	bool esLaClaveCorrecta(string nombreUsuario,string clave);

	~BaseDeDatos();
private:

	void inicializarColumnas();
	void cargarColumnas();

};

#endif /* BASEDEDATOS_H_ */
