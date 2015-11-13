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

	this->estado = estado;

	//this->respuesta["Estado"] = estado;

}
void Respuesta::agregarDatos(const string &datos){

	Value json;
	Reader lector;

	lector.parse(datos,json,false);

	if ( !json.isArray() ){

		this->respuesta = json;

	}else{

		Value salida;

		this->respuesta["Archivos"] = json;

	}

}
void Respuesta::agregarMensaje(const string &mensaje){

	this->mensaje = mensaje;

	//this->respuesta["Mensaje"] = mensaje;

}
string Respuesta::obtenerRespuesta(){

	if ( this->mensaje != "" )
		this->respuesta["Mensaje"] = this->mensaje;
	if ( this->estado != "" )
		this->respuesta["Estado"] = this->estado;

	return respuesta.toStyledString();

}

Respuesta::~Respuesta() {
	// TODO Auto-generated destructor stub
}

