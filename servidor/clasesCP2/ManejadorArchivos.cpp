/*
 * ManejadorArchivos.cpp
 *
 *  Created on: 5 de nov. de 2015
 *      Author: mafv
 */

#include "ManejadorArchivos.h"

ManejadorArchivos::ManejadorArchivos() {

}

string ManejadorArchivos::crearArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;
	string hashArchivo = archivo.crearArchivo(nombreUsuario,datosDelArchivo);
	if(hashArchivo != ""){
		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje(hashArchivo);

	}else{
		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("No se pudo crear el archivo");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::eliminarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;
	archivo.eliminarArchivo(datosDelArchivo);

	respuesta.agregarEstado("OK");
	respuesta.agregarMensaje("Archivo enviado a la papelera");

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::compartirArchivo(const string &datosDelArchivo){

	Archivo archivo;
	Value usuarios;
	Value datos;
	Reader lector;
	Respuesta respuesta;

	lector.parse(datosDelArchivo,datos);

	usuarios = datos["Usuarios"];

	string hashArchivo = archivo.compartir(usuarios.toStyledString(),datosDelArchivo);

	respuesta.agregarEstado("OK");
	respuesta.agregarMensaje("El archivo fue compartido");

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::actualizarArchivo(const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		string hashArchivo = archivo.actualizar(datosDelArchivo);
		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje(hashArchivo);

	}catch (ArchivoInexistente e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("No existe el archivo a actualizar");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::restaurarArchivo(const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		archivo.restaurar(datosDelArchivo);
		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("Archivo restaurado");

	}catch(ArchivoInexistente e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo a restaurar no existe");

	}

	return respuesta.obtenerRespuesta();

}

ManejadorArchivos::~ManejadorArchivos() {
}

