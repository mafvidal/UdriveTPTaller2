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

	try{

		string hashArchivo = archivo.crearArchivo(nombreUsuario,datosDelArchivo);

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje(hashArchivo);

	}catch (LimiteDeCuota l){

			respuesta.agregarEstado("ERROR");
			respuesta.agregarMensaje("El archivo supera el limite de cuota");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::eliminarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;
	const string &resultado = archivo.eliminarArchivo(nombreUsuario,datosDelArchivo);

	if( resultado == "OK" ){

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("Archivo enviado a la papelera");

	}else if ( resultado == "NoEsPropietario" ){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("Solo el propietario puede eliminar el archivo");

	}

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

	string resultado = archivo.compartir(usuarios.toStyledString(),datosDelArchivo);

	if( resultado == "OK" ){

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("El archivo fue compartido");

	}else if ( resultado == "" ){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo a compartir no existe");

	}else{

		respuesta.agregarEstado("WARNIG");
		respuesta.agregarMensaje("Los ususarios: "+resultado+" no existen");

	}


	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::actualizarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		string hashArchivo = archivo.actualizar(nombreUsuario,datosDelArchivo);

		if( hashArchivo != "" ){

			respuesta.agregarEstado("OK");
			respuesta.agregarMensaje(hashArchivo);

		}

	}catch (ArchivoInexistente e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("No existe el archivo a actualizar");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::restaurarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		const string &resultado = archivo.restaurar(nombreUsuario,datosDelArchivo);

		if( resultado == "OK" ){

			respuesta.agregarEstado("OK");
			respuesta.agregarMensaje("Archivo restaurado");

		}else if ( resultado == "Version0" ){

			respuesta.agregarEstado("ERROR");
			respuesta.agregarMensaje("No existe una version del archivo a restaurar");

		}


	}catch(ArchivoInexistente e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo a restaurar no existe");

	}

	return respuesta.obtenerRespuesta();

}

ManejadorArchivos::~ManejadorArchivos() {
}

