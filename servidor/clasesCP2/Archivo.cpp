/*
 * Archivo.cpp
 *
 *  Created on: 23 de oct. de 2015
 *      Author: mafv
 */

#include "Archivo.h"

Archivo::Archivo() {

	this->baseDeDatos = BasedeDatos::obteberInstancia();

}

string Archivo::crearArchivo(const string &usuario,const string &json){

	Value datos;
	Value datosAGuardar;
	Value metadatos;
	Value usuarios(arrayValue);
	Reader lector;
	Hash hash;
	//Usuario usuarioAGuardar;

	lector.parse(json,datos,false);

	const string nombreArchivo = usuario + datos.get("Directorio","").asString()+datos.get("Nombre","").asString()+datos.get("Extension","").asString();

	const string hashArchivo = hash.obtenerHashNuevo(nombreArchivo);

	//usuarios.append(usuario);

	datosAGuardar["Usuarios"] = usuarios;
	datosAGuardar["Eliminado"] = false;

	metadatos["Propietario"] = datos.get("Propietario","").asString();
	metadatos["Nombre"] = datos.get("Nombre","").asString();
	metadatos["Extension"] = datos.get("Extension","").asString();
	metadatos["Directorio"] = datos.get("Directorio","").asString();
	metadatos["Etiquetas"] = datos["Etiquetas"];
	metadatos["Version"] = 0;

	datosAGuardar["MetaDatos"] = metadatos;

	Usuario usuarioAGuardar;
	usuarioAGuardar.agregarArchivo(usuario,hashArchivo);
	this->guardarMetadatosAUsuarios(usuario,datos,hashArchivo);
	//Guardo los metadatos del archivo en la base de datos
	if (this->baseDeDatos->guardar(ARCHIVOS,hashArchivo,datosAGuardar.toStyledString()))

		return hashArchivo;

	else

		return "";



}

void Archivo::eliminarArchivo(const string &json){

	Value datos;
	Value datosAEliminar;
	Value metadatos;
	Reader lector;
	Hash hash;
	Usuario usuario;

	lector.parse(json,datosAEliminar,false);

	const string nombre = datosAEliminar.get("Propietario","").asString() + datosAEliminar.get("Directorio","").asString() + datosAEliminar.get("Nombre","").asString() + datosAEliminar.get("Extension","").asString();

	string hashArchivo = hash.obtenerHashDelArchivo(nombre);

	string datosDelArchivo = this->baseDeDatos->leer(ARCHIVOS,hashArchivo);

	lector.parse(datosDelArchivo,datos,false);

	datos["Eliminado"] = true;

	this->baseDeDatos->guardar(ARCHIVOS,hashArchivo,datos.toStyledString());

	for ( unsigned int indice = 0; indice < datos["Usuarios"].size(); ++indice ){

		const string nombreUsuario = (datos["Usuarios"])[indice].asString();

		usuario.eliminarArchivoCompartido(nombreUsuario,hashArchivo);
		usuario.enviarALaPapelera(nombreUsuario,hashArchivo);

	}

	usuario.eliminarArchivo(datosAEliminar.get("Propietario","").asString(),hashArchivo);
	usuario.enviarALaPapelera(datosAEliminar.get("Propietario","").asString(),hashArchivo);

}

Value Archivo::obtenerDatos(const string & hashDelArchivo){


	Value datos;
	Value metadatos;
	Value metadatosNuevos;
	Reader lector;

	const string datosDelArchivo = this->baseDeDatos->leer(ARCHIVOS,hashDelArchivo);

	lector.parse(datosDelArchivo,datos);
	metadatos = datos["MetaDatos"];

	metadatosNuevos["Propietario"] = metadatos.get("Propietario","").asString();
	metadatosNuevos["Nombre"] = metadatos.get("Nombre","").asString();
	metadatosNuevos["Extension"] = metadatos.get("Extension","").asString();
	metadatosNuevos["Directorio"] = metadatos.get("Directorio","").asString();
	metadatosNuevos["Version"] = metadatos.get("Version",0).asUInt();
	metadatosNuevos["Etiquetas"] = metadatos["Etiquetas"];
	metadatosNuevos["UsuarioQueModifico"] = metadatos.get("UsuarioQueModifico","").asString();
	metadatosNuevos["FechaDeModificacion"] = metadatos.get("FechaDeModificacion","").asString();

	return metadatosNuevos;

}

void Archivo::compartir(const string &usuariosACompartir,const string & json){

	Usuario usuario;
	Value usuarios;
	Value compartido;
	Reader lector;
	Value datos;
	Value datosDelArchivo;
	Hash hash;

	lector.parse(json,datos,false);

	const string nombreCompleto = datos.get("Propietario","").asString() + datos.get("Directorio","").asString() + datos.get("Nombre","").asString() + datos.get("Extension","").asString();

	const string hashDelArchivo = hash.obtenerHashDelArchivo(nombreCompleto);

	//
	lector.parse(this->baseDeDatos->leer(ARCHIVOS,hashDelArchivo),compartido,false);
	//compartido = compartido["Usuarios"];

	lector.parse(usuariosACompartir,usuarios);

	datosDelArchivo = this->obtenerDatos(hashDelArchivo);

	for ( unsigned int indice = 0; indice < usuarios.size(); ++indice ){

		const string nombreUsuario = usuarios[indice].asString();

		compartido["Usuarios"].append(nombreUsuario);

		usuario.agregarArchivoCompartido(nombreUsuario,hashDelArchivo);

		this->guardarMetadatosAUsuarios(nombreUsuario,datosDelArchivo,hashDelArchivo);

	}

	this->baseDeDatos->guardar(ARCHIVOS,hashDelArchivo,compartido.toStyledString());

}

void Archivo::actualizar(const string & json){

	Actualizador actualizador(json);

	actualizador.actualizarArchivo();

}

void Archivo::restaurar(const string & json){

	Restaurador restarador(json);

	restarador.restaurarArchivo();

}

Archivo::~Archivo() {

}

void Archivo::guardarMetadatosAUsuarios(const string &usuario,const Value &datos,const string &hash){

	//Guardo los metadatos de las etiquetas para el archivo
	Value etiquetas(arrayValue);
	etiquetas = datos["Etiquetas"];

	for ( unsigned int indice = 0; indice < etiquetas.size(); ++indice ){

		const string etiqueta = etiquetas[indice].asString();
		this->guardarMetadato(ETIQUETAS,usuario,etiqueta,hash);

	}

	//Guardo el metadato Nombre para el archivo
	this->guardarMetadato(NOMBRE,usuario,datos.get("Nombre","").asString(),hash);
	//Guardo el metadato Extension para el archivo
	this->guardarMetadato(EXTENSION,usuario,datos.get("Extension","").asString(),hash);
	//Guardo el metadato Propietario para el archivo
	this->guardarMetadato(PROPIETARIO,usuario,datos.get("Propietario","").asString(),hash);

	//usuarioAGuardar.agregarArchivo(usuario,hash);

}

void Archivo::guardarMetadato(const unsigned int &TIPO,const string &usuario,const string &metadato,const string & hashArchivo){

	Value datos;
	Value archivos(arrayValue);

	const string &nombre = usuario+metadato;
	const string metadatos = this->baseDeDatos->leer(TIPO,nombre);

	if (metadatos != ""){

		Reader lector;

		lector.parse(metadatos,datos,false);
		archivos = datos["Archivos"];

	}

	archivos.append(hashArchivo);
	datos["Archivos"] = archivos;

	this->baseDeDatos->guardar(TIPO,nombre,datos.toStyledString());

}

string Archivo::obtenerMetadatos(const Value &metadatos){

	Value datos;
	Value metadatosNuevos;
	Reader lector;

	metadatosNuevos["Propietario"] = metadatos.get("Propietario","").asString();
	metadatosNuevos["Nombre"] = metadatos.get("Nombre","").asString();
	metadatosNuevos["Extension"] = metadatos.get("Extension","").asString();
	metadatosNuevos["Directorio"] = metadatos.get("Directorio","").asString();
	metadatosNuevos["Version"] = metadatos.get("Version",0).asUInt();
	metadatosNuevos["Etiquetas"] = metadatos["Etiquetas"];
	metadatosNuevos["UsuarioQueModifico"] = metadatos.get("UsuarioQueModifico","").asString();
	metadatosNuevos["FechaDeModificacion"] = metadatos.get("FechaDeModificacion","").asString();

	return metadatosNuevos.toStyledString();

}

string Archivo::convertirAString(const unsigned int &valor){

	string hashString;
	ostringstream convertir;
	convertir << valor;
	hashString = convertir.str();

	return hashString;

}
