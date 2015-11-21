/*
 * ManejadorArchivosFisicos.h
 *
 *  Created on: 7 de nov. de 2015
 *      Author: mafv
 */

#ifndef MANEJADORARCHIVOSFISICOS_H_
#define MANEJADORARCHIVOSFISICOS_H_

#include "mongoose.h"
#include <iostream>
#include "Constantes.h"
#include "BaseDeDatos.h"
#include "json/json.h"
#include "Respuesta.h"
#include "Usuario.h"
#include "ControladorActualizacion.h"
#include "Excepciones.h"
#include "Log.h"
#include <stdlib.h>
#include <fcntl.h>
#include <map>

using namespace std;
using namespace Json;

/**
* Clase encargada de actualizar, crear y enviar
* los archivos fisicos del cliente
*/
class ManejadorArchivosFisicos {
private:
	Log *log;
	BasedeDatos *baseDeDatos;
	ControladorActualizacion * controladorActualizacion;
	string IDArchivo;
public:
	/**
	* Inicializa los datos necesarios para crear el archivo fisico, y verifica el hashArchivo
	* @params hashArchivo ID del archivo logico que se relaciona con el fisico.
	*/
	ManejadorArchivosFisicos(const string &hashArchivo);
	/**
	* Inicializa los datos necesarios para crear el archivo fisico
	*/
	ManejadorArchivosFisicos();
	/**
	* Permite crear archivos fisicos
	* @params struct mg_connection *c datos de la conexion.
	* @params struct http_message hm datos del archivo.
	*/
	void crearArchivoFisico(struct mg_connection *c,struct http_message hm);
	/**
	* Permite actualizar el archivo fisico
	* @params struct mg_connection *c datos de la conexion.
	* @params struct http_message hm datos del archivo.
	*/
	void actualizarArchivoFisico(struct mg_connection *c,struct http_message hm);
	/**
	* Guarda la foto del usuario
	* @params struct mg_connection *c datos de la conexion.
	* @params struct http_message hm datos del archivo.
	* @params usuario nombre del usuario al que pertenece la foto.
	*/
	void guardarFoto(struct mg_connection *c,struct http_message hm,const string &usuario);
	/**
	* Metodo intermedio para almacenar los datos del archivo fisico
	* @params struct mg_connection *c datos de la conexion.
	*/
	void cargarArchivo(struct mg_connection *c);
	/**
	* Metodo que permite actualizar el nombre del archivo
	* @params archivoActual id del archivo actual.
	* @params archivoActual id del archivo que reemplaza al actual.
	*/
	void actualizar(const string &archivoActual,const string &archivoNuevo);
	/**
	* Metodo que permite enviar los archivo al usuario
	* @params struct mg_connection *c datos de la conexion.
	* @params IDArchivo id del archivo pedido por el cliente.
	* @params version numero de la version del archivo que desea el cliente.
	*/
	void enviarArchivo(struct mg_connection *c,const string &IDArchivo,const int &version);
	virtual ~ManejadorArchivosFisicos();
private:
	string convertirAString(const unsigned int &version);
	void obtenerID(const string &IDArchivo,const int &version);
};

#endif /* MANEJADORARCHIVOSFISICOS_H_ */
