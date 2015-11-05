/*
 * Respuesta.cpp
 *
 *  Created on: 5 de nov. de 2015
 *      Author: mafv
 */

#include "Respuesta.h"

Respuesta::Respuesta() {

}

void Respuesta::agregarEstado(const string &estado){

	this->respuesta["Estado"] = estado;

}
void Respuesta::agregarDatos(const string &datos){

	Value json;
	Reader lector;

	lector.parse(datos,json,false);

	this->respuesta["Datos"] = json;

}
void Respuesta::agregarMensaje(const string &mensaje){

	this->respuesta["Mensaje"] = mensaje;

}
string Respuesta::obtenerRespuesta(){

	return respuesta.toStyledString();

}

Respuesta::~Respuesta() {
	// TODO Auto-generated destructor stub
}

