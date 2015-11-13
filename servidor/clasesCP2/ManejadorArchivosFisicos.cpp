/*
 * ManejadorArchivosFisicos.cpp
 *
 *  Created on: 7 de nov. de 2015
 *      Author: mafv
 */

#include "ManejadorArchivosFisicos.h"

ManejadorArchivosFisicos::ManejadorArchivosFisicos(const string &hashArchivo) {

	this->baseDeDatos = BasedeDatos::obteberInstancia();
	this->controladorActualizacion = ControladorActualizacion::obteberInstanciaControlador();

	this->IDArchivo = hashArchivo;

	if( this->baseDeDatos->leer(ARCHIVOS,this->IDArchivo) == "" )
		throw EArchivoInexistente();

}

ManejadorArchivosFisicos::ManejadorArchivosFisicos(){

	this->baseDeDatos = BasedeDatos::obteberInstancia();
	this->controladorActualizacion = ControladorActualizacion::obteberInstanciaControlador();

}

void ManejadorArchivosFisicos::crearArchivoFisico(struct mg_connection *c,struct http_message hm){

	struct datosArchivo *datos;

	c->proto_handler = NULL;

	datos = new datosArchivo;

	datos->hashArchivo = "./Udrive/"+this->IDArchivo;//= this->inicializarEstructura();

	datos->bytes_left = hm.body.len;

	FILE *archivo;

	archivo = fopen (datos->hashArchivo.c_str(), "wb");

	//Si otro usuario esta actualizando el mismo archivo espera a que finalice la actualizacion
	while(this->controladorActualizacion->seEstaActualizandoElArchivo(datos->hashArchivo,archivo)){
		sleep(5);
	}

	c->user_data = (void *) datos;

	mbuf_remove(&c->recv_mbuf, hm.body.p - c->recv_mbuf.buf);

}

void ManejadorArchivosFisicos::actualizarArchivoFisico(struct mg_connection *c,struct http_message hm){

	Value datos;
	Reader lector;

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,this->IDArchivo),datos,false);

	string hashAnterior = datos.get("HashVersionAnterior","").asString();

	//cout<<this->baseDeDatos->leer(ARCHIVOS,hashAnterior)<<endl;

	rename(("./Udrive/"+this->IDArchivo).c_str(),("./Udrive/"+hashAnterior).c_str());

	this->crearArchivoFisico(c,hm);

}

void ManejadorArchivosFisicos::guardarFoto(struct mg_connection *c,struct http_message hm,const string &usuario){

	this->IDArchivo = usuario;

	if( this->baseDeDatos->leer(USUARIOS,this->IDArchivo) == "" )
			throw EUsuarioInexistente();

	Value datos;
	Reader lector;

	this->crearArchivoFisico(c,hm);

}

void ManejadorArchivosFisicos::cargarArchivo(struct mg_connection *c){

	struct datosArchivo *datos = (struct datosArchivo *) c->user_data;

	size_t to_write = datos->bytes_left, written = 0;

	if (c->recv_mbuf.len < to_write)

		to_write = c->recv_mbuf.len;

	FILE * archivo = this->controladorActualizacion->obtenerArchivo(datos->hashArchivo);//this->archivos[datos->hashArchivo];

	written = fwrite(c->recv_mbuf.buf, 1, to_write, archivo);

	mbuf_remove(&c->recv_mbuf, written);
	datos->bytes_left -= written;

	if (datos->bytes_left <= 0) {

		Respuesta respuesta;
		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("Archivo creado correctamente");

		const string &z=respuesta.obtenerRespuesta();

		mg_printf(c, "HTTP/1.0 200 OK\r\nContent-Length: %d\r\n"
					"Content-Type: application/json\r\n\r\n%s",
					(int) z.size(), z.c_str());

		//fclose(this->archivos[datos->hashArchivo]);
		fclose(archivo);

		this->controladorActualizacion->archivoActualizado(datos->hashArchivo);
		//this->archivos.erase(datos->hashArchivo);
		delete datos;

		c->user_data = NULL;

		c->flags |= MG_F_SEND_AND_CLOSE;

	}

}

string ManejadorArchivosFisicos::inicializarEstructura(){

	Value datos;
	Reader lector;

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,this->IDArchivo),datos,false);

	Directorio directorio;

	string rutaCompleta = directorio.crearDirectorios(datos["MetaDatos"].get("Propietario","").asString()+"/"+datos["MetaDatos"].get("Directorio","").asString());

	return rutaCompleta+datos["MetaDatos"].get("Nombre","").asString()+"."+datos["MetaDatos"].get("Extension","").asString();

}

void ManejadorArchivosFisicos::actualizar(const string &archivoActual,const string &archivoNuevo){

	ifstream source(archivoActual.c_str(), ios::binary);
	ofstream dest(archivoNuevo.c_str(), ios::binary);

	dest << source.rdbuf();

	source.close();
	dest.close();

	//Elimino el archivo antiguo
	remove(archivoActual.c_str());

}

void ManejadorArchivosFisicos::enviarArchivo(struct mg_connection *c,const string &IDArchivo){

	string ruta = "Udrive/"+IDArchivo;

	ifstream archivo(ruta, std::ifstream::binary);

	if( archivo ){

		archivo.seekg (0, archivo.end);
		int length = archivo.tellg();
		archivo.seekg (0, archivo.beg);

		char * buffer = new char [length];

		archivo.read (buffer,length);

		mg_send(c,buffer,length);

		c->flags |= MG_F_SEND_AND_CLOSE;

		delete [] buffer;

		archivo.close();

	} else{

		Respuesta respuesta;
		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo no existe");
		const string &error = respuesta.obtenerRespuesta();
		mg_printf(c, "HTTP/1.0 200 OK\r\nContent-Length: %d\r\n"
					"Content-Type: application/json\r\n\r\n%s",
					(int) error.size(), error.c_str());

	}

}



ManejadorArchivosFisicos::~ManejadorArchivosFisicos() {
}
string ManejadorArchivosFisicos::convertirAString(const unsigned int &version){

	string hashString;
	ostringstream convertir;
	convertir << version;
	hashString = convertir.str();

	return hashString;

}
