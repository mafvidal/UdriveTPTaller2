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

/**
* Clase que permite calcular el hash de un archivo
*/
class Hash {
private:
	BasedeDatos *baseDeDatos;
public:
	Hash();
	/**
	* Obtine el hash del archivo existente
	*/
	string obtenerHashDelArchivo(const string &nombreCompleto);
	/**
	* Obtine el hash de un archivo nuevo
	*/
	string obtenerHashNuevo(const string &nombreCompleto);
	virtual ~Hash();
private:
	unsigned int obtenerHash(const string &nombreCompleto);
	string convertirAString(const unsigned int &hash);
};

#endif /* HASH_H_ */
