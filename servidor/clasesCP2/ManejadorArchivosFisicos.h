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
#include "Directorio.h"
#include <stdlib.h>
#include <map>

using namespace std;
using namespace Json;

class ManejadorArchivosFisicos {
private:
	static map<string,FILE*> archivos;
	BasedeDatos *baseDeDatos;
	string hashArchivo;
public:
	ManejadorArchivosFisicos(const string &hashArchivo);
	void compartir(const string &usuario);
	ManejadorArchivosFisicos();
	void crearArchivoFisico(struct mg_connection *c,struct http_message hm);
	void actualizarArchivoFisico(struct mg_connection *c,struct http_message hm);
	void cargarArchivo(struct mg_connection *c);
	void actualizar(const string &archivoActual,const string &archivoNuevo);
	virtual ~ManejadorArchivosFisicos();
private:
	string inicializarEstructura();
	string convertirAString(const unsigned int &version);
};

#endif /* MANEJADORARCHIVOSFISICOS_H_ */
