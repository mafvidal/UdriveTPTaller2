/*
 * Hash.cpp
 *
 *  Created on: 22 de oct. de 2015
 *      Author: mafv
 */

#include "Hash.h"

Hash::Hash() {

	this->baseDeDatos = BasedeDatos::obteberInstancia();

}

string Hash::obtenerHashDelArchivo(const string &nombreCompleto){

	Reader lector;
	Value datos;

	unsigned int hash = this->obtenerHash(nombreCompleto);
	string hashDelArchivo = this->convertirAString(hash);

	string datosDelArchivo = this->baseDeDatos->leer(ARCHIVOS,hashDelArchivo);

	lector.parse(datosDelArchivo,datos,false);

	string nombreActual = datos["MetaDatos"].get("Propietario","").asString() + datos["MetaDatos"].get("Directorio","").asString() + datos["MetaDatos"].get("Nombre","").asString() + datos["MetaDatos"].get("Extension","").asString();

	//Busco que no exista una colision con el hash
	while( (nombreActual != nombreCompleto) && (nombreActual != "") ){
		cout<<"Estoy";
		hash++;
		hashDelArchivo = this->convertirAString(hash);
		datosDelArchivo = this->baseDeDatos->leer(ARCHIVOS,hashDelArchivo);
		lector.parse(datosDelArchivo,datos,false);
		nombreActual = datos.get("Usuario","").asString() + datos.get("Directorio","").asString() + datos.get("Nombre","").asString() + datos.get("Extension","").asString();

	}

	if(nombreActual==""){
		return "";
	}

	return this->convertirAString(hash);

}

string Hash::obtenerHashNuevo(const string &nombreCompleto){

	unsigned int hash = this->obtenerHash(nombreCompleto);
	string hashDelArchivo = this->convertirAString(hash);

	//Busco que no exista una colision con el hash
	while(this->baseDeDatos->leer(ARCHIVOS,hashDelArchivo) != ""){

		hash++;
		hashDelArchivo = this->convertirAString(hash);

	}

	return this->convertirAString(hash);

}

Hash::~Hash() {
	// TODO Auto-generated destructor stub
}

unsigned int Hash::obtenerHash(const string &nombreCompleto){

	unsigned int hash = 0;

	for(unsigned int i=0; i<nombreCompleto.size(); ++i)
	{
		hash += nombreCompleto[i];
		hash += (hash << 10);
 		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;

}
string Hash::convertirAString(const unsigned int &hash){

	string hashString;
	ostringstream convertir;
	convertir << hash;
	hashString = convertir.str();

	return hashString;

}
