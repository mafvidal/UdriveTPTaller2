#include "DatosDeArchivos.h"

DatosDeArchivos::DatosDeArchivos(){

}
DatosDeArchivos::DatosDeArchivos(string datos){

	Value root;
	Reader reader;

	reader.parse(datos, root,false);

	this->directorio = root.get("Directorio","").asString();
	this->nombre = root.get("Nombre","").asString();
	this->ultimaModificacion = root.get("UltimaFechaModificacion","").asString();
	this->usuarioQueModifico = root.get("UsuarioQueModifico","").asString();
	this->propietario = root.get("Propietario","").asString();
	this->extension = root.get("Extension","").asString();

	Value etiquetas = root["Etiquetas"];
	for ( int indice = 0; indice < etiquetas.size(); ++indice )
		this->etiquetas.push_back(etiquetas[indice].asString());

}

void DatosDeArchivos::setDatos(string datos){

	Value root;
	Reader reader;

	reader.parse(datos, root,false);

	this->directorio = root["MetaDatos"].get("Directorio","").asString();
	this->nombre = root["MetaDatos"].get("Nombre","").asString();
	this->ultimaModificacion = root["MetaDatos"].get("UltimaFechaModificacion","").asString();
	this->usuarioQueModifico = root["MetaDatos"].get("UsuarioQueModifico","").asString();
	this->propietario = root["MetaDatos"].get("Propietario","").asString();
	this->extension = root["MetaDatos"].get("Extension","").asString();

	Value etiquetas = root["MetaDatos"]["Etiquetas"];
	for ( int indice = 0; indice < etiquetas.size(); ++indice )
		this->etiquetas.push_back(etiquetas[indice].asString());

}
void DatosDeArchivos::agregarEtiqueta(string etiqueta){

	this->etiquetas.push_back(etiqueta);

}

void DatosDeArchivos::setUsuarioCompartido(string usuario){

	this->compartido.push_back(usuario);

}
list<string> DatosDeArchivos::getEtiquetas(){

	return this->etiquetas;

}

void DatosDeArchivos::setMetaDatos(string metadatos){

	Value root;
	Reader reader;

	reader.parse(metadatos, root,false);

	this->directorio = root.get("Directorio","").asString();
	this->nombre = root.get("Nombre","").asString();
	this->ultimaModificacion = root.get("UltimaFechaModificacion","").asString();
	this->usuarioQueModifico = root.get("UsuarioQueModifico","").asString();
	this->propietario = root.get("Propietario","").asString();
	this->extension = root.get("Extension","").asString();

	Value etiquetas = root["Etiquetas"];
	for ( int indice = 0; indice < etiquetas.size(); ++indice ){
		this->etiquetas.push_back(etiquetas[indice].asString());
	}

}

string DatosDeArchivos::getDatos(){

	Value datos;
	Value metadatos;
	Value etiquetas(arrayValue);
	Value compartido(arrayValue);

	for (list<string>::iterator it = this->compartido.begin(); it != this->compartido.end(); it++)
		compartido.append(Value((*it)));
	datos["Compartido"] = compartido;

	metadatos["Etiquetas"] = etiquetas;
	metadatos["Directorio"] = this->directorio;
	metadatos["Nombre"] = this->nombre;
	metadatos["UltimaFechaModificacion"] = this->ultimaModificacion;
	metadatos["UsuarioQueModifico"] = this->usuarioQueModifico;
	metadatos["Propietario"] = this->propietario;
	metadatos["Extension"] = this->extension;
	for (list<string>::iterator it = this->etiquetas.begin(); it != this->etiquetas.end(); it++)
			etiquetas.append(Value((*it)));
	metadatos["Etiquetas"] = etiquetas;

	datos["MetaDatos"] =  metadatos;

	return datos.toStyledString();

}
string DatosDeArchivos::getMetadatosDatos(){

	Value metadatos;
	Value etiquet(arrayValue);

	for (list<string>::iterator it = this->etiquetas.begin(); it != this->etiquetas.end(); it++)
		etiquet.append(Value((*it)));
	metadatos["Etiquetas"] = etiquet;
	metadatos["Directorio"] = this->directorio;
	metadatos["Nombre"] = this->nombre;
	metadatos["UltimaFechaModificacion"] = this->ultimaModificacion;
	metadatos["UsuarioQueModifico"] = this->usuarioQueModifico;
	metadatos["Propietario"] = this->propietario;
	metadatos["Extension"] = this->extension;

	return metadatos.toStyledString();

}
string DatosDeArchivos::getNombreCompleto(){

	string nombreCompleto;

	nombreCompleto = this->propietario + this->directorio + this->nombre + "." + this->extension;

	return nombreCompleto;

}

DatosDeArchivos::~DatosDeArchivos(){
}
