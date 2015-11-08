/*
 * Directorio.h
 *
 *  Created on: 8 de nov. de 2015
 *      Author: mafv
 */

#ifndef DIRECTORIO_H_
#define DIRECTORIO_H_

#include <sys/dir.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "Hash.h"

using namespace std;

class Directorio {
public:
	Directorio();
	void crearDirectorioPrincipal(string directorioPrincipal);
	string crearDirectorios(string directorios);
	virtual ~Directorio();
};

#endif /* DIRECTORIO_H_ */
