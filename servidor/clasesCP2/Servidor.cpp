/*
 * Servidor.cpp
 *
 *  Created on: 3 de nov. de 2015
 *      Author: mafv
 */

#include "Servidor.h"

Servidor::Servidor() {
	this->salir=false;
}

void *tomarConsulta(void *threadid)
{

	Datos * datos = (Datos *)threadid;

	AdministradorServidor as(datos->c,datos->ev,datos->p);
	as.administrar();

	//delete datos->p;
	delete datos;

}

void ev_handler(struct mg_connection *c, int ev, void *p) {

	if (ev == MG_EV_HTTP_REQUEST) {

		pthread_t threads;

		Datos *datos = new Datos;
		datos->c= c;
		datos->ev = ev;
		//datos->p = new http_message;
		datos->p = *(struct http_message *)p;

		int resultado = pthread_create(&threads, NULL,tomarConsulta, datos);

		if (resultado){
			cout << "Error:unable to create thread," << resultado << endl;
			exit(-1);
		}

	}

}

void Servidor::arrancar(){

	struct mg_mgr mgr;
	struct mg_connection *nc;

	mg_mgr_init(&mgr, this);
	nc = mg_bind(&mgr, s_http_port, ev_handler);
	mg_set_protocol_http_websocket(nc);

	while (!this->salir) {

		mg_mgr_poll(&mgr, 1000);

	}
	mg_mgr_free(&mgr);

}

void Servidor::detener(){
	this->salir=true;
}

Servidor::~Servidor() {
}
