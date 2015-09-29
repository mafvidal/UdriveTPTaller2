#ifndef DATOSETIQUETAS_H_
#define DATOSETIQUETAS_H_

#include <iostream>
#include <list>
#include <json/json.h>
#include <fstream>

using namespace std;
using namespace Json;

class DatosEtiquetas {
public:
	DatosEtiquetas();
	//Retorna el json con solamente el archivo pasado
	string contruir(string hashArchivo);
	//Agrega un archivo al json existente
	string cargarArchivo(string etiquetasJson,string hashArchivo);
	//Elimina un archivo del json existente
	string eliminarArchivo(string etiquetasJson,string hashArchivo);
	//Retorna la lista de hash de archivos
	list<string> archivos(string etiquetasJson);
	~DatosEtiquetas();

};

#endif /* DATOSETIQUETAS_H_ */
