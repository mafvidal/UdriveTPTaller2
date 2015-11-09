/*
 * Restaurador.cpp
 *
 *  Created on: 2 de nov. de 2015
 *      Author: mafv
 */

#include "Restaurador.h"

Restaurador::Restaurador(const string &datosARestaurar) {

	this->baseDeDatos = BasedeDatos::obteberInstancia();
	this->cargarDatos(datosARestaurar);

	if( this->hashVersionActual == "" ){
		ArchivoInexistente e;
		throw e;
	}

}

void Restaurador::restaurarArchivo(){

	this->restaurarHashAUsuarios();
	this->restaurarMetadato(NOMBRE,this->nombre,this->hashVersionARestaurar,this->propietario);
	this->eliminarMetadato(NOMBRE,this->nombreActual,this->hashVersionActual,this->propietario);
	this->restaurarMetadato(EXTENSION,this->extension,this->hashVersionARestaurar,this->propietario);
	this->eliminarMetadato(EXTENSION,this->extensionActual,this->hashVersionActual,this->propietario);
	this->restaurarMetadato(PROPIETARIO,this->propietario,this->hashVersionARestaurar,this->propietario);
	this->eliminarMetadato(PROPIETARIO,this->propietario,this->hashVersionActual,this->propietario);

	this->restaurarUsuariosCompartidos(NOMBRE,this->nombre,this->nombreActual);
	this->restaurarUsuariosCompartidos(EXTENSION,this->extension,this->extensionActual);
	this->restaurarUsuariosCompartidos(PROPIETARIO,this->propietario,this->propietario);

	this->restaurarEtiquetas();

	if( this->etiquetasAgregadas.size() > 0 ){

		this->eliminarEtiquetasAgregadas();

	}

	const string &nuevoArchivo = this->generarArchivo();

	this->baseDeDatos->eliminar(ARCHIVOS,this->hashVersionActual);
	this->baseDeDatos->eliminar(ARCHIVOS,this->hashVersionPrevia);
	this->baseDeDatos->guardar(ARCHIVOS,this->hashVersionARestaurar,nuevoArchivo);

}

Restaurador::~Restaurador() {
}

void Restaurador::restaurarHashAUsuarios(){

	Usuario usuario;

	usuario.eliminarArchivo(this->propietario,this->hashVersionActual);
	usuario.agregarArchivo(this->propietario,this->hashVersionARestaurar);

	for ( unsigned int indice = 0; indice < this->usuarios.size(); ++indice ){

		const string nombreUsuario = this->usuarios[indice].asString();

		usuario.eliminarArchivoCompartido(nombreUsuario,this->hashVersionActual);
		usuario.agregarArchivoCompartido(nombreUsuario,this->hashVersionARestaurar);

	}

}

void Restaurador::cargarDatos(const string &datosARestaurar){

	Reader lector;
	Value datos;
	Hash hash;

	lector.parse(datosARestaurar,datos,false);

	this->propietario = datos.get("Propietario","").asString();
	this->usuarioQueModifico = datos.get("UsuarioQueModifico","").asString();
	this->fechaDeModificacion = datos.get("FechaDeModificacion","").asString();

	this->hashVersionActual = hash.obtenerHashDelArchivo(datos.get("Propietario","").asString()+datos.get("Directorio","").asString()+datos.get("Nombre","").asString()+datos.get("Extension","").asString());

	if(this->hashVersionActual == "")
		return;

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,this->hashVersionActual),this->ultimaVersion,false);

	this->hashVersionPrevia = this->ultimaVersion.get("HashVersionAnterior","").asString();

	this->usuarios = this->ultimaVersion["Usuarios"];
	this->nombreActual = this->ultimaVersion["MetaDatos"].get("Nombre","").asString();
	this->extensionActual = this->ultimaVersion["MetaDatos"].get("Extension","").asString();

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,this->hashVersionPrevia),datos,false);
	this->nombre = datos.get("Nombre","").asString();
	this->directorio = datos.get("Directorio","").asString();
	this->extension = datos.get("Extension","").asString();
	this->etiquetas = datos["Etiquetas"];
	this->etiquetasEliminadas = datos["EtiquetasEliminadas"];
	this->etiquetasAgregadas = datos["EtiquetasAgregadas"];
	this->hashVersionAnterior = datos.get("HashVersionAnterior","").asString();
	this->hashVersionARestaurar = hash.obtenerHashNuevo(this->propietario+this->directorio+this->nombre+this->extension);

}

void Restaurador::restaurarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario){

	Reader lector;
	Value datos;

	const string nombreMetadato = usuario + metadato;

	string datosMetadato = this->baseDeDatos->leer(TIPO,nombreMetadato);

	if ( datosMetadato != "" ){

		lector.parse(datosMetadato,datos,false);

	}

	//Verificar si fuciona si esta vacio
	datos["Archivos"].append(hashArchivo);

	this->baseDeDatos->guardar(TIPO,nombreMetadato,datos.toStyledString());

}

void Restaurador::eliminarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario){

	Reader lector;
	Value datos;
	Value archivosExistentes(arrayValue);
	Value archivos(arrayValue);

	const string &nombreMetadato = usuario + metadato;

	string datosMetadato = this->baseDeDatos->leer(TIPO,nombreMetadato);

	lector.parse(datosMetadato,datos,false);

	archivosExistentes = datos["Archivos"];

	for ( unsigned int indice = 0; indice < archivosExistentes.size(); ++indice ){

		if(archivosExistentes[indice].asString() != hashArchivo ){

			archivos.append(Value(archivosExistentes[indice].asString()));

		}

	}

	if( archivos.size() == 0 ){

		this->baseDeDatos->eliminar(TIPO,nombreMetadato);

	}else{

		datos["Archivos"] = archivos;

		this->baseDeDatos->guardar(TIPO,nombreMetadato,datos.toStyledString());

	}

}

void Restaurador::restaurarUsuariosCompartidos(const unsigned int &TIPO,  const string &metadatoGuardar,const string &metadatoEliminar){

	for ( unsigned int indice = 0; indice < this->usuarios.size(); ++indice ){

		const string nombreUsuario = this->usuarios[indice].asString();

		this->restaurarMetadato(TIPO,metadatoGuardar,this->hashVersionARestaurar,nombreUsuario);
		this->eliminarMetadato(TIPO,metadatoEliminar,this->hashVersionActual,nombreUsuario);

	}

}

void Restaurador::restaurarEtiquetas(){

	for ( unsigned int indice = 0; indice < this->etiquetas.size(); ++indice ){

		const string &etiqueta = this->etiquetas[indice].asString();

		this->restaurarMetadato(ETIQUETAS,etiqueta,this->hashVersionARestaurar,this->propietario);
		this->eliminarMetadato(ETIQUETAS,etiqueta,this->hashVersionActual,this->propietario);

		this->restaurarUsuariosCompartidos(ETIQUETAS,etiqueta,etiqueta);

	}

}

void Restaurador::eliminarEtiquetasAgregadas(){

	for ( unsigned int indice = 0; indice < this->etiquetasAgregadas.size(); ++indice ){

		const string &etiqueta = this->etiquetasAgregadas[indice].asString();

		this->eliminarMetadato(ETIQUETAS,etiqueta,this->hashVersionActual,this->propietario);

		for ( unsigned int indice = 0; indice < this->usuarios.size(); ++indice ){

			const string &nombreUsuario = this->usuarios[indice].asString();

			this->eliminarMetadato(ETIQUETAS,etiqueta,this->hashVersionActual,nombreUsuario);

		}

	}

}

string Restaurador::generarArchivo(){

	Value nuevoArchivo;
	Value metadatos;

	nuevoArchivo["Usuarios"] = this->usuarios;
	metadatos["Propietario"] = this->propietario;
	metadatos["Nombre"] = this->nombre;
	metadatos["Extension"] = this->extension;
	metadatos["Directorio"] = this->directorio;
	metadatos["Etiquetas"] = this->etiquetas;
	metadatos["Version"] = this->ultimaVersion["MetaDatos"].get("Version",0).asUInt()-1;
	metadatos["UsuarioQueModifico"] = this->usuarioQueModifico;
	metadatos["FechaDeModificacion"] = this->fechaDeModificacion;
	nuevoArchivo["MetaDatos"] = metadatos;
	nuevoArchivo["Eliminado"] = false;
	nuevoArchivo["HashVersionAnterior"] = this->hashVersionAnterior;

	return nuevoArchivo.toStyledString();

}
