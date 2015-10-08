#include "ManejadorDB.h"

ManejadorDB::ManejadorDB(BaseDeDatos * db){

	this->db = db;
}

bool ManejadorDB::registrarUsuario(string registroJson){


	string usuario;
	string clave;
	float cuota;
	Value datos;
	Value metadatos;
	Reader reader;

	reader.parse(registroJson, datos,false);

	usuario = datos.get("Usuario","").asString();
	clave = datos.get("Clave","").asString();
	cuota = datos.get("Cuota","").asFloat();

	metadatos["Nombre"] = datos.get("Nombre","").asString();
	metadatos["Email"] = datos.get("Email","").asString();
	metadatos["UltimaUbicacion"] = datos.get("UltimaUbicacion","").asString();
	metadatos["Foto"] = datos.get("Foto","").asString();


	if ( this->db->existeUsuario(usuario)){
		return false;
	}

	this->db->agregarUsuario(usuario,clave,metadatos.toStyledString(),cuota);

	return true;

}

bool ManejadorDB::iniciarsesion(string sesionJson){

	string usuario;
	string clave;
	Value datos;
	Reader reader;

	reader.parse(sesionJson, datos,false);

	usuario = datos.get("Usuario","").asString();
	clave = datos.get("Clave","").asString();

	if ( this->db->existeUsuario(usuario) )
		return false;

	return this->db->esLaClaveCorrecta(usuario,clave);

}

bool ManejadorDB::agregarArchivo(string archivoJson){

	string usuario;
	float espacio;
	Value metadatos;
	Value datos;
	Reader reader;

	reader.parse(archivoJson, datos,false);

	usuario = datos.get("Usuario","").asString();
	espacio = datos.get("Espacio","").asFloat();

	metadatos = datos["Metadatos"];

	if ( this->db->existeUsuario(usuario) )
		return false;
	
	if ( this->db->cuotaDisponible(usuario) <= espacio )
		return false;

	this->db->agregarArchivo(usuario,metadatos.toStyledString(),espacio);

	return true;

}

string ManejadorDB::obtenerListaArchivos(string usuarioJson){

	string usuario;
	Value datos;
	Value archivos;
	Value archivo;
	Reader reader;
	list<string> listaArchivos;

	reader.parse(usuarioJson, datos,false);

	usuario = datos.get("Usuario","").asString();

	listaArchivos = this->db->getArchivos(usuario);

	for(list<string>::iterator it = listaArchivos.begin(); it != listaArchivos.end(); it++){

		reader.parse((*it), archivo,false);

		archivos.append(archivo);

	}

	return archivos.toStyledString();

}

void ManejadorDB::eliminarArchivo(string archivoJson){

	string usuario;
	float espacio;
	Value metadatos;
	Value datos;
	Reader reader;

	reader.parse(archivoJson, datos,false);

	usuario = datos.get("Usuario","").asString();
	espacio = datos.get("Espacio","").asFloat();

	metadatos = datos["Metadatos"];

	this->db->eliminarLogicamenteArchivo(usuario,metadatos.toStyledString(),espacio);

}

string ManejadorDB::verPapelera(string usuarioJson){

	string usuario;
	Value datos;
	Value archivos;
	Value archivo;
	Reader reader;
	list<string> listaArchivos;

	reader.parse(usuarioJson, datos,false);

	usuario = datos.get("Usuario","").asString();

	listaArchivos = this->db->getArchivosEnPapelera(usuario);

	for(list<string>::iterator it = listaArchivos.begin(); it != listaArchivos.end(); it++){

		reader.parse((*it), archivo,false);

		archivos.append(archivo);

	}

	return archivos.toStyledString();

}

void ManejadorDB::eliminarArchivoDePapelera(string archivoJson){

	string usuario;
	Value metadatos;
	Value datos;
	Reader reader;

	reader.parse(archivoJson, datos,false);

	usuario = datos.get("Usuario","").asString();

	metadatos = datos["Metadatos"];

	this->db->eliminarFisicamenteArchivo(usuario,metadatos.toStyledString());

}

ManejadorDB::~ManejadorDB(){


}
