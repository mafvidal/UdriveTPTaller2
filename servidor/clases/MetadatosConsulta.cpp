#include "MetadatosConsulta.h"

MetadatosConsulta::MetadatosConsulta(){}

string MetadatosConsulta::contruir(string hashArchivo){

	Value datos;
	Value archivos(arrayValue);

	archivos.append(Value(hashArchivo));

	datos["Archivos"] = archivos;

	return datos.toStyledString();

}

string MetadatosConsulta::cargarArchivo(string datosjson,string hashArchivo){

	Value datos;
	Reader reader;

	reader.parse(datosjson, datos,false);

	datos["Archivos"].append(Value(hashArchivo));

	return datos.toStyledString();

}

string MetadatosConsulta::eliminarArchivo(string datosjson,string hashArchivo){

	Value datos;
	Reader reader;
	Value archivosNuevos(arrayValue);
	Value archivos(arrayValue);

	reader.parse(datosjson, datos,false);

	archivos = datos["Archivos"];

	for ( int indice = 0; indice < archivos.size(); ++indice ){
		if(archivos[indice].asString() != hashArchivo ){
			archivosNuevos.append(Value(archivos[indice].asString()));
		}
	}

	datos["Archivos"] = archivosNuevos;

	return datos.toStyledString();

}
list<string> MetadatosConsulta::archivos(string datosjson){

	Value datos;
	Reader reader;
	list<string> archivosLista;

	reader.parse(datosjson, datos,false);

	Value archivos = datos["Archivos"];
	for ( int indice = 0; indice < archivos.size(); ++indice )
		archivosLista.push_back(archivos[indice].asString());

	return archivosLista;

}

MetadatosConsulta::~MetadatosConsulta(){}
