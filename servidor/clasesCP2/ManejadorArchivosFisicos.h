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
#include "Archivo.h"
#include "BaseDeDatos.h"
#include "json/json.h"
#include <sys/dir.h>
#include "Directorio.h"
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
	ManejadorArchivosFisicos();
	void crearArchivoFisico(struct mg_connection *c,struct http_message hm);
	void cargarArchivo(struct mg_connection *c);
	string obtenerNombreDelArchivo(const string &hashArchivo);
	virtual ~ManejadorArchivosFisicos();
};

#endif /* MANEJADORARCHIVOSFISICOS_H_ */
