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
#include "Log.h"

/*
* Clase encargada de administrar los archivos
* segun lo enviado por el servidor
*/
class ManejadorArchivos {
private:
	Log *log;
public:
	ManejadorArchivos();
	/**
	* Metodo que permite crear un archivo logico
	* @params nombreUsuario nombre del usuario que crea el archivo.
	* @params datosDelArchivo datos del archivo a crear.
	*/
	string crearArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	/**
	* Metodo que permite eliminar un archivo logico
	* @params nombreUsuario nombre del usuario que eliminar el archivo.
	* @params datosDelArchivo datos del archivo a eliminar.
	*/
	string eliminarArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	/**
	* Permite compartir un archivo con una serie de usuarios
	* @params datosDelArchivo posee los datos del archivo a compartir y la lista de usuarios.
	*/
	string compartirArchivo(const string &datosDelArchivo);
	/**
	* Metodo que permite actualizar un archivo logico
	* @params nombreUsuario nombre del usuario que actualiza el archivo.
	* @params datosDelArchivo datos del archivo a actualizar.
	*/
	string actualizarArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	/**
	* Metodo que permite restaurar un archivo a una version anterior
	* @params nombreUsuario nombre del usuario que restaura el archivo.
	* @params datosDelArchivo datos del archivo a rastaurar.
	*/
	string restaurarArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	/**
	* Metodo que permite recuperar un archivo de la papelera
	* @params nombreUsuario nombre del usuario que recupera el archivo de la papelera.
	* @params datosDelArchivo datos del archivo a recuperar del papelera.
	*/
	string recuperarArchivo(const string &nombreUsuario,const string &datosDelArchivo);
	virtual ~ManejadorArchivos();
};

#endif /* MANEJADORARCHIVOS_H_ */
