#ifndef METADATOSCONSULTA_H_
#define METADATOSCONSULTA_H_

#include <iostream>
#include <list>
#include <json/json.h>
#include <fstream>

using namespace std;
using namespace Json;

class MetadatosConsulta {
public:
	MetadatosConsulta();
	//Retorna el json con solamente el archivo pasado
	string contruir(string hashArchivo);
	//Agrega un archivo al json existente
	string cargarArchivo(string datosjson,string hashArchivo);
	//Elimina un archivo del json existente
	string eliminarArchivo(string datosjson,string hashArchivo);
	//Retorna la lista de hash de archivos
	list<string> archivos(string datosjson);
	~MetadatosConsulta();

};

#endif /* METADATOSCONSULTA_H_ */
