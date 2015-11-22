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

/**
* Clase encargada de administrar las busquedas
* segun lo recibido por el servidor
*/
class ManejadorBuscador {
public:
	ManejadorBuscador();
	/**
	* Permite buscar archivos por una determida etiqueta
	* @param nombreUsuario nombre del usuario del cual se quieren los metadatos de los archivos.
	* @param metadato etiqueta por la cual se desea realizar la busqueda
	* @return retorna la lista de archivos que posee el usuario, y coinciden con la etiqueta
	*/
	string buscarPorEtiquetas(const string &nombreUsuario,const string &metadato);
	/**
	* Permite buscar archivos por un determido nombre de archivo
	* @param nombreUsuario nombre del usuario del cual se quieren los metadatos de los archivos.
	* @param metadato nombre de archivo por el cual se desea realizar la busqueda
	* @return retorna la lista de archivos que posee el usuario, y coinciden con el nombre
	*/
	string buscarPorNombre(const string &nombreUsuario,const string &metadato);
	/**
	* Permite buscar archivos por un determido propietario
	* @param nombreUsuario nombre del usuario del cual se quieren los metadatos de los archivos.
	* @param metadato propietario de archivo por el cual se desea realizar la busqueda
	* @return retorna la lista de archivos que posee el usuario, y coinciden con el propietario
	*/
	string buscarPorPropietario(const string &nombreUsuario,const string &metadato);
	/**
	* Permite buscar archivos por un determida extension de archivo
	* @param nombreUsuario nombre del usuario del cual se quieren los metadatos de los archivos.
	* @param metadato extension del archivo por el cual se desea realizar la busqueda
	* @return retorna la lista de archivos que posee el usuario, y coinciden con la extension
	*/
	string buscarPorExtension(const string &nombreUsuario,const string &metadato);
	virtual ~ManejadorBuscador();
};

#endif /* MANEJADORBUSCADOR_H_ */
