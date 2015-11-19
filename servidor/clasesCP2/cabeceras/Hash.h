/*
 * Hash.h
 *
 *  Created on: 22 de oct. de 2015
 *      Author: mafv
 */

#ifndef HASH_H_
#define HASH_H_

#include "BaseDeDatos.h"
#include "Constantes.h"
#include <sstream>
#include <iostream>
#include "json/json.h"

using namespace Json;
using namespace std;

class Hash {
private:
	BasedeDatos *baseDeDatos;
public:
	Hash();
	string obtenerHashDelArchivo(const string &nombreCompleto);
	//Obtiene un hash que no es utilizado en la base de datos
	string obtenerHashNuevo(const string &nombreCompleto);
	virtual ~Hash();
private:
	unsigned int obtenerHash(const string &nombreCompleto);
	string convertirAString(const unsigned int &hash);
};

#endif /* HASH_H_ */
