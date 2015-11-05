/*
 * ManejadorUsuario.h
 *
 *  Created on: 3 de nov. de 2015
 *      Author: mafv
 */

#ifndef MANEJADORUSUARIO_H_
#define MANEJADORUSUARIO_H_

#include "Usuario.h"
#include "json/json.h"
#include "Respuesta.h"

class ManejadorUsuario {
public:
	ManejadorUsuario();
	string generar(const string &nombreUsuario,const string &datosUsuario);
	string iniciarSesion(const string &nombreUsuario,const string &datosUsuario);
	string obtenerDatos(const string &nombreUsuario);
	string actualizarDatos(const string &nombreUsuario,const string &datosUsuario);
	string obtenerArchivos(const string &nombreUsuario);
	string obtenerArchivosPapelera(const string &nombreUsuario);
	virtual ~ManejadorUsuario();
};

#endif /* MANEJADORUSUARIO_H_ */
