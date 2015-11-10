
#include "ManejadorUsuario.h"

ManejadorUsuario::ManejadorUsuario() {

}

string ManejadorUsuario::generar(const string &nombreUsuario,const string &datosUsuario){

	Respuesta respuesta;
	Usuario usuario;

	if ( usuario.registrarse(nombreUsuario,datosUsuario) ){

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("Se registro correctamente el usuario");

	}else{

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("Error usuario existente");

	}



	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::iniciarSesion(const string &nombreUsuario,const string &datosUsuario){


	Respuesta respuesta;
	Usuario usuario;

	if (usuario.identificarse(nombreUsuario,datosUsuario)){

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("Inicio existoso");

	}else{

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("Usuario o clave incorrecta");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::obtenerDatos(const string &nombreUsuario){

	Respuesta respuesta;
	Usuario usuario;
	const string &datosUsuario = usuario.obtenerDatos(nombreUsuario);

	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(datosUsuario);

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::actualizarDatos(const string &nombreUsuario,const string &datosUsuario){

	Respuesta respuesta;
	Usuario usuario;

	usuario.actualizarDatos(nombreUsuario,datosUsuario);

	respuesta.agregarEstado("OK");
	respuesta.agregarMensaje("datos actualizados correctamente");

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::obtenerArchivos(const string &nombreUsuario){

	Respuesta respuesta;
	Usuario usuario;

	const string &archivos = usuario.obtenerArchivos(nombreUsuario);

	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(archivos);

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::obtenerArchivosCompartidos(const string &nombreUsuario){

	Respuesta respuesta;
	Usuario usuario;

	const string &archivos = usuario.obtenerArchivosCompartidos(nombreUsuario);

	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(archivos);

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::obtenerArchivosPapelera(const string &nombreUsuario){

	Respuesta respuesta;
	Usuario usuario;

	const string &archivosPapelera = usuario.verPapelera(nombreUsuario);

	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(archivosPapelera);

	return respuesta.obtenerRespuesta();

}


ManejadorUsuario::~ManejadorUsuario() {
}

