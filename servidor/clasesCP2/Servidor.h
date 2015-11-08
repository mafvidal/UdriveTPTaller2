/*
 * Servidor.h
 *
 *  Created on: 3 de nov. de 2015
 *      Author: mafv
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "mongoose.h"
#include <iostream>
#include "ManejadorUsuario.h"
#include "AdministradorServidor.h"
#include <pthread.h>
#include <fstream>
#include <map>
#include <unistd.h>


using namespace std;

static const char *s_http_port = "8000";
static map<string,FILE *> mapa;

class Servidor {
private:

	bool salir;
public:
	friend void ev_handler(struct mg_connection *c, int ev, void *p);
	friend void *tomarConsulta(void *threadid);
	Servidor();
	void arrancar();
	void detener();
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
