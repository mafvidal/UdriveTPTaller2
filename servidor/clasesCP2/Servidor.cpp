#include "Servidor.h"

Servidor::Servidor() {

	this->salir=false;

}

void ev_handler(struct mg_connection *c, int ev, void *p) {

	if (ev == MG_EV_HTTP_REQUEST || ev == MG_EV_RECV ) {

		AdministradorServidor as(c,ev,*(struct http_message *)p);
		as.administrar();

	}

}


void Servidor::arrancar(){


	struct mg_mgr mgr;
	struct mg_connection *nc;

	mg_mgr_init(&mgr, this);
	nc = mg_bind(&mgr, s_http_port, ev_handler);
	mg_set_protocol_http_websocket(nc);

	mg_enable_multithreading(nc);
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
