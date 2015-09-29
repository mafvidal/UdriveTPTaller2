#include "DatosDeArchivos.h"

DatosDeArchivos::DatosDeArchivos(){

}

string DatosDeArchivos::obtenerDatos(string metadatosJson){

	Value metadatos;
	Value datos;
	Reader reader;
	Value compartido(arrayValue);

	reader.parse(metadatosJson, metadatos,false);

	datos["Compartido"] = compartido;
	datos["MetaDatos"] = metadatos;

	return datos.toStyledString();

}
string DatosDeArchivos::obtenerMetadatos(string datosJson){

	Value metadatos;
	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	metadatos = datos["MetaDatos"];

	return metadatos.toStyledString();

}
string DatosDeArchivos::agregarUsuarioCompartido(string datosJson,string usuarioNuevo){

	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	datos["Compartido"].append(Value(usuarioNuevo));

	return datos.toStyledString();

}
string DatosDeArchivos::agregarEtiqueta(string datosJson,string etiqueta){

	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	datos["MetaDatos"]["Etiquetas"].append(Value(etiqueta));

	return datos.toStyledString();

}

string DatosDeArchivos::getNombreCompleto(string datosJson){

	string nombreCompleto;
	string propietario;
	string directorio;
	string nombre;
	string extension;
	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	propietario = datos["MetaDatos"].get("Propietario","").asString();
	directorio = datos["MetaDatos"].get("Directorio","").asString();
	nombre = datos["MetaDatos"].get("Nombre","").asString();
	extension = datos["MetaDatos"].get("Extension","").asString();

	nombreCompleto = propietario + directorio + nombre + "." + extension;

	return nombreCompleto;

}
string DatosDeArchivos::modificarMetadatos(string datosJson,string metaDatosJson){

	Value datosNuevos;
	Value datos;
	Value metadatos;
	Reader reader;
	Value compartido(arrayValue);

	reader.parse(datosJson, datos,false);
	reader.parse(metaDatosJson, metadatos,false);

	compartido = datos["Compartido"];

	datosNuevos["Compartido"] = compartido;
	datosNuevos["MetaDatos"] = metadatos;

	return datosNuevos.toStyledString();

}
DatosDeArchivos::~DatosDeArchivos(){
}

