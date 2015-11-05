/*
 * Archivo.h
 *
 *  Created on: 23 de oct. de 2015
 *      Author: mafv
 */

#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include "BaseDeDatos.h"
#include "json/json.h"
#include "Constantes.h"
#include "Actualizador.h"
#include "Restaurador.h"
#include "Hash.h"
#include "Usuario.h"
#include <iostream>

using namespace Json;
using namespace std;

class Archivo {
private:
	BasedeDatos *baseDeDatos;
public:
	Archivo();
	//Almacena en la base de datos, los metadatos del archivo
	//El archivo es agregado por primera vez a la base de datos
	//Retorna si se pudo o no guardar el archivo
	bool crearArchivo(const string &usuario,const string &json);
	//Elimina el archivo enviandolo a la papelera
	//Recibe los datos del archivo
	void eliminarArchivo(const string &json);
	//¿?
	Value obtenerDatos(const string & hashDelArchivo);
	//Comparte el archivo segun el json, con los usuariosACompartir
	void compartir(const string &usuariosACompartir,const string & json);
	void actualizar(const string & json);
	void restaurar(const string & json);
	virtual ~Archivo();
private:
	void guardarMetadatosAUsuarios(const string &usuario,const Value &datos,const string &hash);
	void guardarMetadato(const unsigned int &TIPO,const string &usuario,const string &metadato,const string & hashArchivo);
	string obtenerMetadatos(const Value &metadatos);
	string convertirAString(const unsigned int &valor);
};

#endif /* ARCHIVO_H_ */
