
#ifndef DATOSDEUSUARIO_H_
#define DATOSDEUSUARIO_H_

#include <iostream>
#include <list>
#include <json/json.h>
#include <fstream>

using namespace std;
using namespace Json;

class DatosDeUsuario {
private:
	string clave;
	float cuota;
	float cuotaUsada;
	string nombre;
	string email;
	string ubicacionFoto;
	string ultimaUbicacion;
	list<string> archivos;
public:
	DatosDeUsuario(string clave,float cuota);
	DatosDeUsuario(string datos);
	//Carga los metadatos del usuario
	void cargarDatosDelUsuario(string datosDeUsuario);
	//Retorna el json con los datos del usuario
	string getDatos();
	//Retorna el json con los metadatos del usuario
	string getDatosDelUsuario();
	//Modifica la clave del usuario
	void setClave(string clave);
	//Agrega un archivo de un espacio determinado
	void setArchivo(string archivo, float espacio);
	//retorna la lista de archivos
	list<string> getArchivos();
	//Modifica la cuota maxima del usuario
	void setCuota(float cuota);
	//Retorna la clave
	string getClave();
	virtual ~DatosDeUsuario();
private:
	//Puede ser privado
	void cargarDatos(string datos);
};

#endif /* DATOSDEUSUARIO_H_ */
