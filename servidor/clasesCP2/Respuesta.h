/*
 * Respuesta.h
 *
 *  Created on: 5 de nov. de 2015
 *      Author: mafv
 */

#ifndef RESPUESTA_H_
#define RESPUESTA_H_

#include "json/json.h"
#include <iostream>

using namespace std;
using namespace Json;

class Respuesta {
private:
	Value respuesta;
	string estado;
	string mensaje;
public:
	Respuesta();
	void agregarEstado(const string &estado);
	void agregarDatos(const string &datos);
	void agregarMensaje(const string &mensaje);
	string obtenerRespuesta();
	virtual ~Respuesta();
};

#endif /* RESPUESTA_H_ */
