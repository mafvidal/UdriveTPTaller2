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
#include "Log.h"

using namespace std;

static map<string,FILE *> mapa;

/*
* Clase encargada de escuchar nuevos clientes
*/
class Servidor {
private:
	Log *log;
	bool salir;
public:
	friend void ev_handler(struct mg_connection *c, int ev, void *p);
	friend void *tomarConsulta(void *threadid);
	Servidor();
	/*
	* Arranca el servidor
	*/
	void arrancar();
	/*
	* Detiene el servidor
	*/
	void detener();
	/*
	* Retorna si el servidor se esta ejecuntando o no
	*/
	bool ok();
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
