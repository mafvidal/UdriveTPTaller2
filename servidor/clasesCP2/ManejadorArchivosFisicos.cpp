/*
 * ManejadorArchivosFisicos.cpp
 *
 *  Created on: 7 de nov. de 2015
 *      Author: mafv
 */

#include "ManejadorArchivosFisicos.h"

map<string,FILE*> ManejadorArchivosFisicos::archivos;

ManejadorArchivosFisicos::ManejadorArchivosFisicos(const string &hashArchivo) {

	this->baseDeDatos = BasedeDatos::obteberInstancia();

	this->hashArchivo = hashArchivo;

}

ManejadorArchivosFisicos::ManejadorArchivosFisicos(){

	this->baseDeDatos = BasedeDatos::obteberInstancia();

}

void ManejadorArchivosFisicos::compartir(const string &usuario){

	Value datos;
	Reader lector;

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,hashArchivo),datos,false);

	Directorio directorio;

	string nombreArchivo = datos["MetaDatos"].get("Nombre","").asString()+"."+datos["MetaDatos"].get("Extension","").asString();

	string rutaOrigen = "./Udrive/"+datos["MetaDatos"].get("Propietario","").asString()+datos["MetaDatos"].get("Directorio","").asString()+nombreArchivo;

	string rutaDestino = directorio.crearDirectorios(usuario+"/"+"Compartidos"+"/"+datos["MetaDatos"].get("Propietario","").asString()+datos["MetaDatos"].get("Directorio","").asString())+nombreArchivo;

	cout<<rutaOrigen<<endl;
	cout<<rutaDestino<<endl;

	//this->copiaArchivo(rutaOrigen,rutaDestino);
	//system("copy \"rutaOrigen\" \"rutaDestino\"");

}

void ManejadorArchivosFisicos::crearArchivoFisico(struct mg_connection *c,struct http_message hm){

	struct datosArchivo *datos;

	c->proto_handler = NULL;

	datos = new datosArchivo;

	datos->hashArchivo = "./Udrive/"+this->hashArchivo;//= this->inicializarEstructura();

	datos->bytes_left = hm.body.len;

	FILE *archivo;

	archivo = fopen (datos->hashArchivo.c_str(), "wb");

	this->archivos[datos->hashArchivo] = archivo;

	c->user_data = (void *) datos;

	mbuf_remove(&c->recv_mbuf, hm.body.p - c->recv_mbuf.buf);

}

void ManejadorArchivosFisicos::actualizarArchivoFisico(struct mg_connection *c,struct http_message hm){

	Value datos;
	Reader lector;

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,this->hashArchivo),datos,false);

	string hashAnterior = datos.get("HashVersionAnterior","").asString();

	rename(("./Udrive/"+this->hashArchivo).c_str(),("./Udrive/"+hashAnterior).c_str());

	this->crearArchivoFisico(c,hm);

}

void ManejadorArchivosFisicos::cargarArchivo(struct mg_connection *c){

	struct datosArchivo *datos = (struct datosArchivo *) c->user_data;

	size_t to_write = datos->bytes_left, written = 0;

	if (c->recv_mbuf.len < to_write)

		to_write = c->recv_mbuf.len;

	FILE * archivo = this->archivos[datos->hashArchivo];

	written = fwrite(c->recv_mbuf.buf, 1, to_write, archivo);

	mbuf_remove(&c->recv_mbuf, written);
	datos->bytes_left -= written;

	if (datos->bytes_left <= 0) {

		mg_printf(c,
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: text/plain\r\n"
				"Connection: close\r\n\r\n"
				"Written %ld of POST data to a temp file\n\n",
				(long) ftell(this->archivos[datos->hashArchivo]));

		fclose(this->archivos[datos->hashArchivo]);

		this->archivos.erase(datos->hashArchivo);
		delete datos;


		c->user_data = NULL;

		c->flags |= MG_F_SEND_AND_CLOSE;

	}

}

string ManejadorArchivosFisicos::inicializarEstructura(){

	Value datos;
	Reader lector;

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,hashArchivo),datos,false);

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

ManejadorArchivosFisicos::~ManejadorArchivosFisicos() {
}
string ManejadorArchivosFisicos::convertirAString(const unsigned int &version){

	string hashString;
	ostringstream convertir;
	convertir << version;
	hashString = convertir.str();

	return hashString;

}
