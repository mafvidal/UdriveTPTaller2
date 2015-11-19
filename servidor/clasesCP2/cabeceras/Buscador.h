/*
 * Buscador.h
 *
 *  Created on: 30 de oct. de 2015
 *      Author: mafv
 */

#ifndef BUSCADOR_H_
#define BUSCADOR_H_

#include "BaseDeDatos.h"
#include "json/json.h"
#include "Constantes.h"
#include "Hash.h"
#include "Archivo.h"
#include "Log.h"
#include <iostream>

using namespace Json;
using namespace std;

/**
* Clase que permite buscar archivos en la base de datos, segun sus metadatos
*/
class Buscador {
private:
	Log *log;
	BasedeDatos *baseDeDatos;
public:
	Buscador();
	/**
	* Busca el archivo en la base de datos por su etiqueta
	* @params usuario que desea realizar la busqueda.
	* @params etiqueta etiqueta a buscar.
	* @return retorna la lista de archivos que coincide con la etiqueta
	*/
	string buscarPorEtiqueta(const string &usuario,const string &etiqueta);
	/**
	* Busca el archivo en la base de datos por su propietario
	* @params usuario que desea realizar la busqueda.
	* @params propietario propietario a buscar.
	* @return retorna la lista de archivos que coincide con el propietario.
	*/
	string buscarPorPropietario(const string &usuario,const string &propietario);
	/**
	* Busca el archivo en la base de datos por su nombre
	* @params usuario que desea realizar la busqueda.
	* @params nombre nombre a buscar.
	* @return retorna la lista de archivos que coincide con el nombre.
	*/
	string buscarPorNombre(const string &usuario,const string &nombre);
	/**
	* Busca el archivo en la base de datos por su extension
	* @params usuario que desea realizar la busqueda.
	* @params extension extension a buscar.
	* @return retorna la lista de archivos que coincide con el extension.
	*/
	string buscarPorExtension(const string &usuario,const string &extension);
	virtual ~Buscador();
private:
	string buscarMetadato(const unsigned int &TIPO,const string &metadato);
	Value obtenerDatos(const string & hashDelArchivo);
};

#endif /* BUSCADOR_H_ */
