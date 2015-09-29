#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <iostream>
#include <sstream>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include <vector>
#include <assert.h>
#include <list>
#include "estructuras.h"
#include "DatosDeUsuario.h"
#include "DatosDeArchivos.h"

using namespace std;
using namespace rocksdb;


class BaseDeDatos {
private:
	const int USARIOS=1;
	const int ARCHIVOS=2;
	DB* db;
	Status estado;
	string dirPath;
	vector<ColumnFamilyHandle*> handles;

public:
	BaseDeDatos(string directorio);
	//Agrega un usuario nuevo a la base de datos
	//El usuario no debe existir
	bool agregarUsuario(string nombreUsuario,string clave,string metadatosJson,float cuota);
	//Retorna si el usuario existe o no en la base de datos
	bool existeUsuario(string nombreUsuario);
	//Devuelve si la clave es la del usuario
	//El usuario debe existir
	bool esLaClaveCorrecta(string nombreUsuario,string clave);
	//Devuelve los metadatos del usuario
	//el usuario debe existir
	string getMetaDatosUsuario(string nombreUsuario);
	//Almacena los metaDatos de un usuario
	//Los datos son reemplazados
	bool setDatosUsuario(string nombreUsuario, string metaDatosUsuario);
	//Agregar el nombre del archivo en el directorio
	//El usuario debe existir
	bool agregarArchivo(string nombreUsuario,string metadatos,float espacio);
	//Devuelve la lista de archivos que posee el usuario
	list<string> getArchivos(string nombreUsuario);
	//Elimina logicamente el archivo de la base de datos
	void eliminarLogicamenteArchivo(string nombreUsuario,string metadatosArchivo,float espacio);
	~BaseDeDatos();
private:

	unsigned int obtenerHash(string archivo);
	void inicializarColumnas();
	void cargarColumnas();
	string convertirAString(unsigned int hash);
	//list<Archivo> parsearArchivos(string listaDeArchivos);

};

#endif /* BASEDEDATOS_H_ */
