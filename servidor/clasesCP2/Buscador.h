/*
 * Buscador.h
 *
 *  Created on: 30 de oct. de 2015
 *      Author: mafv
 */

#ifndef BUSCADOR_H_
#define BUSCADOR_H_

#include "BaseDeDatos.h"
#include "json/json.h"
#include "Constantes.h"
#include "Hash.h"
#include "Archivo.h"
#include "Log.h"
#include <iostream>

using namespace Json;
using namespace std;

class Buscador {
private:
	Log *log;
	BasedeDatos *baseDeDatos;
public:
	Buscador();
	string buscarPorEtiqueta(const string &usuario,const string &etiqueta);
	string buscarPorPropietario(const string &usuario,const string &propietario);
	string buscarPorNombre(const string &usuario,const string &nombre);
	string buscarPorExtension(const string &usuario,const string &extension);
	virtual ~Buscador();
private:
	string buscarMetadato(const unsigned int &TIPO,const string &metadato);
};

#endif /* BUSCADOR_H_ */
