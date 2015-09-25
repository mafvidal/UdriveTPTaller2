#ifndef DATOSDEARCHIVOS_H_
#define DATOSDEARCHIVOS_H_

#include <iostream>
#include <list>
#include "json/json.h"
#include <fstream>

using namespace std;
using namespace Json;

class DatosDeArchivos {
private:
	string directorio;
	list<string> compartido;
	string nombre;
	string ultimaModificacion;
	string usuarioQueModifico;
	list<string> etiquetas;
	string propietario;
	string extension;
public:
	DatosDeArchivos();
	DatosDeArchivos(string datos);
	//Modificar datos
	void setDatos(string datos);
	//Modificar metadatos
	void setMetaDatos(string metadatos);
	//Agregar una etiqueta
	void agregarEtiqueta(string etiqueta);
	//Agregar usuario que comparte el archivo
	void setUsuarioCompartido(string usuario);
	list<string> getEtiquetas();
	//Retorna los datos del archivo
	string getDatos();
	//Retorna los metadatos del archivo
	string getMetadatosDatos();
	//Retorna propietario/directorio/nombre
	string getNombreCompleto();
	virtual ~DatosDeArchivos();
};

#endif /* DATOSDEARCHIVOS_H_ */
