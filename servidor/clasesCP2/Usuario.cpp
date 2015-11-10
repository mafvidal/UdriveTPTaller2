/*
 * Usuario.cpp
 *
 *  Created on: 23 de oct. de 2015
 *      Author: mafv
 */

#include "Usuario.h"

Usuario::Usuario() {

	this->baseDeDatos = BasedeDatos::obteberInstancia();

}

bool Usuario::identificarse(const string &usuario,const string &json){

	Reader lector;
	Value datos;
	Value datosExistentes;
	const string datosDelUsuario = this->baseDeDatos->leer(USUARIOS,usuario);

	if ( datosDelUsuario == "" )
		return false;

	lector.parse(json,datos,false);
	lector.parse(datosDelUsuario,datosExistentes,false);

	const string &clave=datos.get("Clave","").asString();

	return ( clave == datosExistentes.get("Clave","").asString() );

}

bool Usuario::registrarse(const string &usuario,const string &json){

	const string datosDelUsuario = this->baseDeDatos->leer(USUARIOS,usuario);

	if( datosDelUsuario != "" )
		return false;

	Value datosACargar;
	Value datosNuevos;
	Value metadatos;
	Reader lector;
	Value archivos(arrayValue);

	lector.parse(json,datosACargar,false);

	datosNuevos["Clave"] = datosACargar.get("Clave","").asString();
	datosNuevos["Cuota"] = datosACargar.get("Cuota","").asString();
	datosNuevos["CuotaUsada"] = CUOTAINICIAL;
	datosNuevos["Archivos"] = archivos;
	datosNuevos["ArchivosCompartidos"] = archivos;
	datosNuevos["Papelera"] = archivos;
	datosNuevos["MetaDatos"] = this->cargarMetadatos(datosACargar["MetaDatos"]);

	return this->baseDeDatos->guardar(USUARIOS,usuario,datosNuevos.toStyledString());

}

string Usuario::obtenerDatos(const string &usuario){

	Value datos;
	Value metadatos;
	Reader lector;

	const string datosDelUsuario = this->baseDeDatos->leer(USUARIOS,usuario);

	lector.parse(datosDelUsuario,datos,false);

	return datos["MetaDatos"].toStyledString();

}

bool Usuario::actualizarDatos(const string &usuario,const string & json){

	Value datosExistentes;
	Value datosNuevos;
	Value metadatos;
	Reader lector;
	Value archivos(arrayValue);

	const string datosDelUsuario = this->baseDeDatos->leer(USUARIOS,usuario);

	lector.parse(datosDelUsuario,datosExistentes,false);
	lector.parse(json,datosNuevos,false);

	datosExistentes["Clave"] = datosNuevos["Clave"];
	datosExistentes["Cuota"] = datosNuevos["Cuota"];
	datosExistentes["MetaDatos"] = this->cargarMetadatos(datosNuevos["MetaDatos"]);

	return this->baseDeDatos->guardar(USUARIOS,usuario,datosExistentes.toStyledString());

}

string Usuario::obtenerArchivos(const string & usuario){

	Value datos;
	Value archivos(arrayValue);
	Reader lector;

	const string datosUsuario = this->baseDeDatos->leer(USUARIOS,usuario);

	lector.parse(datosUsuario,datos,false);

	this->cargarArchivos(archivos,datos["Archivos"]);

	this->cargarArchivos(archivos,datos["ArchivosCompartidos"]);

	return archivos.toStyledString();

}

string Usuario::verPapelera(const string &usuario){

	Value datos;
	Value archivos(arrayValue);
	Reader lector;

	const string datosUsuario = this->baseDeDatos->leer(USUARIOS,usuario);

	lector.parse(datosUsuario,datos,false);

	this->cargarArchivos(archivos,datos["Papelera"]);

	return archivos.toStyledString();

}

void Usuario::eliminarArchivoCompartido(const string &usuario,const string &hashArchivo){

	this->eliminar(usuario,hashArchivo,"ArchivosCompartidos");

}

void Usuario::agregarArchivoCompartido(const string &usuario,const string &hashArchivo){

	this->agregar(usuario,hashArchivo,"ArchivosCompartidos");

}

void Usuario::eliminarArchivo(const string &usuario,const string &hashArchivo){

	this->eliminar(usuario,hashArchivo,"Archivos");

}

void Usuario::agregarArchivo(const string &usuario,const string &hashArchivo){

	this->agregar(usuario,hashArchivo,"Archivos");

}

void Usuario::enviarALaPapelera(const string &nombreUsuario,const string &hashArchivo){

	this->agregar(nombreUsuario,hashArchivo,"Papelera");

}

bool Usuario::existeUsuario(const string &nombreUsuario){

	return (this->baseDeDatos->leer(USUARIOS,nombreUsuario) != "");

}

Usuario::~Usuario() {

}

Value Usuario::cargarMetadatos(const Value &metadatos){

	Value metadatosActualizados;

	metadatosActualizados["Nombre"] = metadatos.get("Nombre","").asString();
	metadatosActualizados["Email"] = metadatos.get("Email","").asString();
	metadatosActualizados["UltimaUbicacion"] = metadatos.get("UltimaUbicacion","").asString();
	metadatosActualizados["Foto"] = metadatos.get("Foto","").asString();

	return metadatosActualizados;

}

void Usuario::cargarArchivos(Value &archivos,const Value &archivosExistentes){

	Reader reader;
	//Value archivo;
	Value metadatos;
	Archivo archivo;

	for ( unsigned int indice = 0; indice < archivosExistentes.size(); ++indice ){

		const string hashArchivo = archivosExistentes[indice].asString();
		const string datosDelArchivo = this->baseDeDatos->leer(ARCHIVOS,hashArchivo);

		archivos.append(archivo.obtenerDatos(hashArchivo));

	}

}

void Usuario::eliminar(const string &usuario,const string &hashArchivo,const string &tipo){

	Value datos;
	Value archivosExistentes(arrayValue);
	Value archivos(arrayValue);
	Reader lector;

	const string datosDelArchivo = this->baseDeDatos->leer(USUARIOS,usuario);

	lector.parse(datosDelArchivo,datos,false);

	archivosExistentes = datos[tipo];

	for ( unsigned int indice = 0; indice < archivosExistentes.size(); ++indice ){

		if(archivosExistentes[indice].asString() != hashArchivo ){

			archivos.append(Value(archivosExistentes[indice].asString()));

		}

	}

	datos[tipo] = archivos;

	this->baseDeDatos->guardar(USUARIOS,usuario,datos.toStyledString());

}

void Usuario::agregar(const string &usuario,const string &hashArchivo,const string &tipo){

	Value datos;
	Reader lector;

	const string datosDelUsuario = this->baseDeDatos->leer(USUARIOS,usuario);

	lector.parse(datosDelUsuario,datos,false);

	datos[tipo].append(hashArchivo);

	this->baseDeDatos->guardar(USUARIOS,usuario,datos.toStyledString());

}

Value Usuario::getMetadatosArchivo(const Value &metadatos){

	Value datos;
	Value metadatosNuevos;
	Reader lector;

	metadatosNuevos["Propietario"] = metadatos.get("Propietario","").asString();
	metadatosNuevos["Nombre"] = metadatos.get("Nombre","").asString();
	metadatosNuevos["Extension"] = metadatos.get("Extension","").asString();
	metadatosNuevos["Directorio"] = metadatos.get("Directorio","").asString();
	metadatosNuevos["Version"] = metadatos.get("Version","").asUInt();
	metadatosNuevos["Etiquetas"] = metadatos["Etiquetas"];
	metadatosNuevos["UsuarioQueModifico"] = metadatos.get("UsuarioQueModifico","").asString();
	metadatosNuevos["FechaDeModificacion"] = metadatos.get("FechaDeModificacion","").asString();

	return metadatosNuevos;

}

