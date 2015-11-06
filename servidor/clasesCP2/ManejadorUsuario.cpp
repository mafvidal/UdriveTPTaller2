
#include "ManejadorUsuario.h"

ManejadorUsuario::ManejadorUsuario() {

}

string ManejadorUsuario::generar(const string &nombreUsuario,const string &datosUsuario){

	Respuesta respuesta;
	Usuario usuario;
	if (usuario.registrarse(nombreUsuario,datosUsuario)){
		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("Se registro correctamente el usuario");
		//return "Se registro correctamente el usuario";
	}else{
		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("Error usuario existente");
		//return "Error usuario existente";
	}

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::iniciarSesion(const string &nombreUsuario,const string &datosUsuario){


	Respuesta respuesta;
	Usuario usuario;
	if (usuario.identificarse(nombreUsuario,datosUsuario)){
		//return "Inicio existoso";
		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("Inicio existoso");
	}else{
		//return "Usuario o clave incorrecta";
		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("Usuario o clave incorrecta");
	}

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::obtenerDatos(const string &nombreUsuario){

	Respuesta respuesta;
	Usuario usuario;
	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(usuario.obtenerDatos(nombreUsuario));
	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::actualizarDatos(const string &nombreUsuario,const string &datosUsuario){

	Respuesta respuesta;
	Usuario usuario;

	if(usuario.actualizarDatos(nombreUsuario,datosUsuario)){

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("datos actualizados correctamente");
		return "datos actualizados correctamente";

	}else{

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("error al actualizar los datos");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::obtenerArchivos(const string &nombreUsuario){

	Respuesta respuesta;
	Usuario usuario;
	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(usuario.obtenerArchivos(nombreUsuario));
	return respuesta.obtenerRespuesta();

}

string ManejadorUsuario::obtenerArchivosPapelera(const string &nombreUsuario){

	Respuesta respuesta;
	Usuario usuario;
	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(usuario.verPapelera(nombreUsuario));
	return respuesta.obtenerRespuesta();

}


ManejadorUsuario::~ManejadorUsuario() {
}

