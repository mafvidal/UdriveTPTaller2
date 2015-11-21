#include "../cabeceras/ManejadorBuscador.h"

ManejadorBuscador::ManejadorBuscador() {

}

string ManejadorBuscador::buscarPorEtiquetas(const string &nombreUsuario,const string &metadato){

	Respuesta respuesta;
	Buscador buscador;
	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(buscador.buscarPorEtiqueta(nombreUsuario,metadato));
	return respuesta.obtenerRespuesta();

}

string ManejadorBuscador::buscarPorNombre(const string &nombreUsuario,const string &metadato){

	Respuesta respuesta;
	Buscador buscador;
	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(buscador.buscarPorNombre(nombreUsuario,metadato));
	return respuesta.obtenerRespuesta();

}

string ManejadorBuscador::buscarPorPropietario(const string &nombreUsuario,const string &metadato){

	Respuesta respuesta;
	Buscador buscador;
	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(buscador.buscarPorPropietario(nombreUsuario,metadato));
	return respuesta.obtenerRespuesta();

}

string ManejadorBuscador::buscarPorExtension(const string &nombreUsuario,const string &metadato){

	Respuesta respuesta;
	Buscador buscador;
	respuesta.agregarEstado("OK");
	respuesta.agregarDatos(buscador.buscarPorExtension(nombreUsuario,metadato));
	return respuesta.obtenerRespuesta();

}

ManejadorBuscador::~ManejadorBuscador() {
}

