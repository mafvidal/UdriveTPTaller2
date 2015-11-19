/*
 * ManejadorBuscador.h
 *
 *  Created on: 5 de nov. de 2015
 *      Author: mafv
 */

#ifndef MANEJADORBUSCADOR_H_
#define MANEJADORBUSCADOR_H_

#include "Buscador.h"
#include "Respuesta.h"

class ManejadorBuscador {
public:
	ManejadorBuscador();
	string buscarPorEtiquetas(const string &nombreUsuario,const string &metadato);
	string buscarPorNombre(const string &nombreUsuario,const string &metadato);
	string buscarPorPropietario(const string &nombreUsuario,const string &metadato);
	string buscarPorExtension(const string &nombreUsuario,const string &metadato);
	virtual ~ManejadorBuscador();
};

#endif /* MANEJADORBUSCADOR_H_ */
