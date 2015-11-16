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

class ManejadorArchivosFisicos {
private:
	Log *log;
	BasedeDatos *baseDeDatos;
	ControladorActualizacion * controladorActualizacion;
	string IDArchivo;
public:
	ManejadorArchivosFisicos(const string &hashArchivo);
	ManejadorArchivosFisicos();
	void crearArchivoFisico(struct mg_connection *c,struct http_message hm);
	void actualizarArchivoFisico(struct mg_connection *c,struct http_message hm);
	void guardarFoto(struct mg_connection *c,struct http_message hm,const string &usuario);
	void cargarArchivo(struct mg_connection *c);
	void actualizar(const string &archivoActual,const string &archivoNuevo);
	void enviarArchivo(struct mg_connection *c,const string &IDArchivo,const int &version);
	virtual ~ManejadorArchivosFisicos();
private:
	string convertirAString(const unsigned int &version);
	void obtenerID(const string &IDArchivo,const int &version);
};

#endif /* MANEJADORARCHIVOSFISICOS_H_ */
