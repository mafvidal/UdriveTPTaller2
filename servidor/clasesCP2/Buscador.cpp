/*
 * Buscador.cpp
 *
 *  Created on: 30 de oct. de 2015
 *      Author: mafv
 */

#include "Buscador.h"

Buscador::Buscador() {

	this->baseDeDatos = BasedeDatos::obteberInstancia();
	this->log = Log::obteberInstanciaLog();

}
string Buscador::buscarPorEtiqueta(const string &usuario,const string &etiqueta){

	return this->buscarMetadato(ETIQUETAS,usuario+etiqueta);

}
string Buscador::buscarPorPropietario(const string &usuario,const string &propietario){

	return this->buscarMetadato(PROPIETARIO,usuario+propietario);

}
string Buscador::buscarPorNombre(const string &usuario,const string &nombre){

	return this->buscarMetadato(NOMBRE,usuario+nombre);

}
string Buscador::buscarPorExtension(const string &usuario,const string &extension){

	return this->buscarMetadato(EXTENSION,usuario+extension);

}


Buscador::~Buscador() {
}
string Buscador::buscarMetadato(const unsigned int &TIPO,const string &metadato){

	Value hashArchivos;
	Value datosArchivos;
	Value archivosMetadatos(arrayValue);
	Reader lector;
	Archivo archivo;

	lector.parse(this->baseDeDatos->leer(TIPO,metadato),hashArchivos,false);

	Value archivos(arrayValue);
	archivos = hashArchivos["Archivos"];

	for ( unsigned int indice = 0; indice < archivos.size(); ++indice ){

		const string hash = archivos[indice].asString();

		this->log->debug("Agregado el archivo: "+hash+" a la busqueda");

		//lector.parse(this->baseDeDatos->leer(ARCHIVOS,hash),datosArchivos,false);
		Value datos = archivo.obtenerDatos(hash);
		//if( datos != Json::nullValue )
		archivosMetadatos.append(datos);

	}

	return archivosMetadatos.toStyledString();

}
