#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <iostream>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include <vector>
#include <assert.h>
#include <list>
#include "estructuras.h"

using namespace std;
using namespace rocksdb;


class BaseDeDatos {
private:
	const int USARIOS=1;
	const int DATOSUSARIOS=2;
	const int ARCHIVOSUSARIOS=3;
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
	//Agregar el nombre del archivo en el directorio
	//El usuario debe existir
	bool agregarArchivo(string nombreUsuario, string archivo);
	//Devuelve la lista de archivos que posee el usuario
	//En una estructura Archivo, que contiene el nombre y la ruta
	list<Archivo> getArchivos(string nombreUsuario);

	~BaseDeDatos();
private:

	void inicializarColumnas();
	void cargarColumnas();
	list<Archivo> parsearArchivos(string listaDeArchivos);

};

#endif /* BASEDEDATOS_H_ */
