/*
 * ManejadorArchivos.h
 *
 *  Created on: 5 de nov. de 2015
 *      Author: mafv
 */

#ifndef MANEJADORARCHIVOS_H_
#define MANEJADORARCHIVOS_H_

#include "Archivo.h"
#include "json/json.h"
#include "Respuesta.h"
#include "ManejadorArchivosFisicos.h"

class ManejadorArchivos {
public:
	ManejadorArchivos();
	string crearArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	string eliminarArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	string compartirArchivo(const string &datosDelArchivo);
	string actualizarArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	string restaurarArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	virtual ~ManejadorArchivos();
};

#endif /* MANEJADORARCHIVOS_H_ */
