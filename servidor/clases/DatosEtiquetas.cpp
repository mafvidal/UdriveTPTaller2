#include "DatosEtiquetas.h"

DatosEtiquetas::DatosEtiquetas(){}

string DatosEtiquetas::contruir(string hashArchivo){

	Value datos;
	Value archivos(arrayValue);

	archivos.append(Value(hashArchivo));

	datos["Archivos"] = archivos;

	return datos.toStyledString();

}

string DatosEtiquetas::cargarArchivo(string etiquetasJson,string hashArchivo){

	Value datos;
	Reader reader;

	reader.parse(etiquetasJson, datos,false);

	datos["Archivos"].append(Value(hashArchivo));

	return datos.toStyledString();

}

string DatosEtiquetas::eliminarArchivo(string etiquetasJson,string hashArchivo){

	Value datos;
	Reader reader;
	Value archivosNuevos(arrayValue);
	Value archivos(arrayValue);

	reader.parse(etiquetasJson, datos,false);

	archivos = datos["Archivos"];

	for ( int indice = 0; indice < archivos.size(); ++indice ){
		if(archivos[indice].asString() != hashArchivo ){
			archivosNuevos.append(Value(archivos[indice].asString()));
		}
	}

	datos["Archivos"] = archivosNuevos;

	return datos.toStyledString();

}
list<string> DatosEtiquetas::archivos(string etiquetasJson){

	Value datos;
	Reader reader;
	list<string> archivosLista;

	reader.parse(etiquetasJson, datos,false);

	Value archivos = datos["Archivos"];
	for ( int indice = 0; indice < archivos.size(); ++indice )
		archivosLista.push_back(archivos[indice].asString());

	return archivosLista;

}

DatosEtiquetas::~DatosEtiquetas(){}
