/*
 * Usuario.h
 *
 *  Created on: 23 de oct. de 2015
 *      Author: mafv
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include "BaseDeDatos.h"
#include "json/json.h"
#include "Constantes.h"
#include <iostream>
#include "Archivo.h"

using namespace Json;
using namespace std;

class Usuario {
private:
	BasedeDatos *baseDeDatos;
public:
	Usuario();
	//Retorna true si se logro identificar correctamente al usuario
	//retorna false si la clave o el usuario son incorrectos
	bool identificarse(const string &usuario,const string &json);
	//Registra al usuario en la base de datos
	//Si el usuario ya existe, no lo registra, y retorna false
	//Si el usuario es registrado correctamente retorna true
	bool registrarse(const string &usuario,const string &json);
	//Retorna los metadatos del usuario
	string obtenerDatos(const string &usuario);
	bool actualizarDatos(const string &usuario,const string & json);
	//Retorna la lista de archivos compartidos y propios del usuario
	string obtenerArchivos(const string & usuario);
	//Retorna los archivos que el usuario posee en la papelera
	string verPapelera(const string &usuario);
	void eliminarArchivoCompartido(const string &usuario,const string &hashArchivo);
	void agregarArchivoCompartido(const string &usuario,const string &hashArchivo);
	void eliminarArchivo(const string &usuario,const string &hashArchivo);
	void agregarArchivo(const string &usuario,const string &hashArchivo);
	void enviarALaPapelera(const string &nombreUsuario,const string &hashArchivo);
	virtual ~Usuario();
private:
	Value cargarMetadatos(const Value &metadatos);
	void cargarArchivos(Value &archivos,const Value &archivosExistentes);
	void eliminar(const string &usuario,const string &hashArchivo,const string &tipo);
	void agregar(const string &usuario,const string &hashArchivo,const string &tipo);
	Value getMetadatosArchivo(const Value &metadatos);
};

#endif /* USUARIO_H_ */
