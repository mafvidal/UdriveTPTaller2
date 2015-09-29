#ifndef DATOSDEARCHIVOS_H_
#define DATOSDEARCHIVOS_H_

#include <iostream>
#include <list>
#include "json/json.h"
#include <fstream>

using namespace std;
using namespace Json;

class DatosDeArchivos {
public:
	DatosDeArchivos();
	//Generar datosArchivo a partir de los metadatos
	string obtenerDatos(string metadatosJson);
	//Retorna los metadatos del archivo
	string obtenerMetadatos(string datosJson);
	//Agrega usuario con el que se comparte el archivo
	string agregarUsuarioCompartido(string datosJson,string usuarioNuevo);
	//Agrega una nueva etiqueta
	string agregarEtiqueta(string datosJson,string etiqueta);
	//Retorna propietario/directorio/nombre
	string getNombreCompleto(string datosJson);
	//Modifica los metadatos actuales por los nuevos
	string modificarMetadatos(string datosJson,string metaDatosJson);
	//Retorna la lista de etiquetas a partir de los metadatos
	list<string> listaDeEtiquetas(string metadatosJson);
	//Retorna el propietario a partir de los metadatos
	string propietario(string metadatosJson);
	//Retorna el nombre del archivo a partir de los metadatos
	string nombre(string metadatosJson);
	//Retorna la extension del archivo a partir de los metadatos
	string extension(string metadatosJson);
	virtual ~DatosDeArchivos();
private:
	string getDato(string metadatosJson, string tipo);
};

#endif /* DATOSDEARCHIVOS_H_ */
