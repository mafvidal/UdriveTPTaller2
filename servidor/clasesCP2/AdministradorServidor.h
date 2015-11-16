#ifndef ADMINISTRADORSERVIDOR_H_
#define ADMINISTRADORSERVIDOR_H_

#include "mongoose.h"
#include <iostream>
#include <sstream>
#include "ManejadorUsuario.h"
#include "ManejadorArchivos.h"
#include "ManejadorArchivosFisicos.h"
#include "ManejadorBuscador.h"
#include "Constantes.h"
#include "Log.h"
#include <map>
#include <unistd.h>

using namespace std;

class AdministradorServidor {
private:
	Log *log;
	struct mg_connection *c;
	int ev;
	struct http_message hm;
	struct Mensaje mensaje;
public:
	AdministradorServidor(struct mg_connection *c, int ev, struct http_message p);
	void administrar();
	virtual ~AdministradorServidor();
private:
	void parsearMensaje();
	int sonIguales(const struct mg_str *s1, const struct mg_str *s2);
	string determinarProtocolo();
	string realizarOperacion();
	void cerrar();

};

#endif /* ADMINISTRADORSERVIDOR_H_ */
