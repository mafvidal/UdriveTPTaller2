#include "Servidor.h"

Servidor::Servidor() {

	this->salir=false;
	this->log = Log::obteberInstanciaLog();

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

	if(nc==NULL){

		this->salir = true;

		this->log->error("Error al conectarse al puerto 8000");

		cout << "Error al conectarse al puerto " << s_http_port <<endl;
		cout << "Presione culquier tecla y enter para salir" << endl;

		return;

	}

	mg_set_protocol_http_websocket(nc);

	//Cada escucha se trata en un nuevo hilo
	mg_enable_multithreading(nc);
	while (!this->salir) {
		mg_mgr_poll(&mgr, 1000);

	}
	mg_mgr_free(&mgr);

}

bool Servidor::ok(){

	return !this->salir;

}

void Servidor::detener(){

	this->log->info("Servidor detenido, finalizando escucha");

	this->salir=true;
}

Servidor::~Servidor() {
}
