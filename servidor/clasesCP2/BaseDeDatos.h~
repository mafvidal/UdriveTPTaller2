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

using namespace std;
using namespace rocksdb;

class BasedeDatos {
private:
	mutex mtx;
	DB* db;
	Status estado;
	string dirPath;
	vector<ColumnFamilyHandle*> handles;
public:
	static BasedeDatos * obteberInstancia();
	bool guardar(const int TIPO,const string &clave,const string &valor);
	const string leer(const int TIPO,const string &clave);
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
