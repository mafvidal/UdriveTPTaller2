/*
 * Constantes.h
 *
 *  Created on: 22 de oct. de 2015
 *      Author: mafv
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include "mongoose.h"
#include <iostream>

using namespace std;

const int CUOTAINICIAL=0;
const int USUARIOS=1;
const int ARCHIVOS=2;
const int ETIQUETAS=3;
const int NOMBRE=4;
const int EXTENSION=5;
const int PROPIETARIO=6;

static const struct mg_str s_put_method = MG_STR("PUT");
static const struct mg_str s_get_method = MG_STR("GET");
static const struct mg_str s_post_method = MG_STR("POST");
static const struct mg_str s_delele_method = MG_STR("DELETE");
static const char *s_http_port = "8000";

struct Mensaje {
  string tipo;
  string quien;
  string metadato;
  string hashArchivo;
  string archivoFisico;
  int version;
};

struct Datos {
	struct mg_connection *c;
	int ev;
	struct http_message p;
};

struct datosArchivo {
	string hashArchivo;
	size_t bytes_left;
};

#endif /* CONSTANTES_H_ */
