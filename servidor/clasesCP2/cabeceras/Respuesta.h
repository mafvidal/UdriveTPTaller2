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

/**
* Clase encargada de armar la respuesta que se va a enviar al cliente
*/
class Respuesta {
private:
	Value respuesta;
	string estado;
	string mensaje;
public:
	Respuesta();
	/**
	* Almacena el estado de la consulta
	* @params estado estado de la consulta.
	*/
	void agregarEstado(const string &estado);
	/**
	* Almacena el los datos resultantes de la consulta
	* @params datos datos a enviar al cliente.
	*/
	void agregarDatos(const string &datos);
	/**
	* Almacena el mensaje que resulto de la consulta
	* @params mensaje mensaje de la consulta.
	*/
	void agregarMensaje(const string &mensaje);
	/**
	* Retorna la respuesta como un string
	*/
	string obtenerRespuesta();
	virtual ~Respuesta();
};

#endif /* RESPUESTA_H_ */
