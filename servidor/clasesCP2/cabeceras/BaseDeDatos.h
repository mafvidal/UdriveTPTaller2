/*
 * BasedeDatos.h
 *
 *  Created on: 19 de oct. de 2015
 *      Author: mafv
 */

#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include <vector>
#include <assert.h>
#include <list>
#include <mutex>
#include "Log.h"

using namespace std;
using namespace rocksdb;

/**
* Clase encargada de administrar la base de datos de Rocksdb
*/
class BasedeDatos {
private:
	Log *log;
	static mutex mtx2;
	mutex mtx;
	DB* db;
	Status estado;
	string dirPath;
	vector<ColumnFamilyHandle*> handles;
public:
	static BasedeDatos * obteberInstancia();
	/**
	* Permite almacenar datos en la base de datos
	* @params TIPO tipo de dato a guardar.
	* @params clave ID que se almacena en la base de datos.
	* @valor valor a guardar en la base de datos.
	* @return retorna se pudo o no guardar
	*/
	bool guardar(const int TIPO,const string &clave,const string &valor);
	/**
	* Permite leer datos en la base de datos
	* @params TIPO tipo de dato a leer.
	* @params clave ID para identificar el dato en la base de datos a leer.
	* @return retorna los datos a leer
	*/
	const string leer(const int TIPO,const string &clave);
	/**
	* Permite eliminar datos en la base de datos
	* @params TIPO tipo de dato a eliminar.
	* @params clave ID que permite identificar el dato a eliminar.
	* @return retorna se pudo o no eliminar
	*/
	bool eliminar(const int TIPO,const string &clave);
	virtual ~BasedeDatos();
private:
	BasedeDatos();
	static void destruirInstancia();
	static BasedeDatos * unicaInstancia;
	void inicializarColumnas();
	void cargarColumnas();
};

#endif /* BASEDEDATOS_H_ */
