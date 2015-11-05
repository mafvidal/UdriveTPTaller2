/*
 * AdministradorServidor.h
 *
 *  Created on: 3 de nov. de 2015
 *      Author: mafv
 */

#ifndef ADMINISTRADORSERVIDOR_H_
#define ADMINISTRADORSERVIDOR_H_

#include "mongoose.h"
#include <iostream>
#include <sstream>
#include "ManejadorUsuario.h"
#include "ManejadorArchivos.h"
#include "ManejadorBuscador.h"
#include "Constantes.h"

using namespace std;

class AdministradorServidor {
private:
	struct mg_connection *c;
	int ev;
	struct http_message hm;
public:
	AdministradorServidor(struct mg_connection *c, int ev, struct http_message p);
	void administrar();
	virtual ~AdministradorServidor();
private:
	void parsearMensaje(struct Mensaje &mensaje);
	int sonIguales(const struct mg_str *s1, const struct mg_str *s2);
	string determinarProtocolo();
	string realizarOperacion(const struct Mensaje &mensaje);
};

#endif /* ADMINISTRADORSERVIDOR_H_ */
