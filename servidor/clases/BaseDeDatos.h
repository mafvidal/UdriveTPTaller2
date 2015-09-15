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
	const int DATOSUSARIOS=2;
	DB* db;
	Status estado;
	string dirPath;
	vector<ColumnFamilyHandle*> handles;

public:
	BaseDeDatos(string directorio);

	//Agrega un usuario nuevo a la base de datos
	//El usuario no debe existir
	bool setUsuario(string nombreUsuario,string clave);
	//Retorna si el usuario existe o no en la base de datos
	bool existeUsuario(string nombreUsuario);
	//Devuelve si la clave es la del usuario
	//El usuario debe existir
	bool esLaClaveCorrecta(string nombreUsuario,string clave);
	//Devuelve los datos del usuario
	//el usuario debe existir
	string getDatosUsuario(string nombreUsuario);
	//Almacena los datos de un usuario
	//Los datos son reemplazados
	bool setDatosUsuario(string nombreUsuario, string datosUsuario);

	~BaseDeDatos();
private:

	void inicializarColumnas();
	void cargarColumnas();

};

#endif /* BASEDEDATOS_H_ */
