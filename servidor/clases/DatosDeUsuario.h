#ifndef DATOSDEUSUARIO_H_
#define DATOSDEUSUARIO_H_

#include <iostream>
#include <list>
#include <json/json.h>
#include <fstream>

using namespace std;
using namespace Json;

class DatosDeUsuario {
public:
	DatosDeUsuario();
	//Construye los Datos de usuario a partir de los metadatos del usuario
	string obtenerDatosDeUsuarios(string metadatosJson,string clave,float cuota);
	//Modifica los datos del usuario a partir de los metadatos del usuario
	string modificarDatosDeUsuarios(string datosJson,string metaDatosJson);
	//Retorna los metadatos del usuario
	string obtenerMetadatosDelUsuario(string datosJson);
	//Modifica la clave
	string modificarClave(string datosJson,string clave);
	//retorna la clave del usuario
	string clave(string datosJson);
	//Agrega un archivo nuevo
	string agregarArchivoNuevo(string datosJson,string hashArchivo,float espacio);
	//Elimina un archivo
	string eliminarArchivo(string datosJson,string hashArchivo,float espacio);
	//Elimina un archivo
	string eliminarArchivoCompartido(string datosJson,string hashArchivo,float espacio);
	//Retorna la cuota asignada al usuario
	float cuota(string datosJson);
	//Retorna la cuota usada por el usuario
	float cuotaUsada(string datosJson);
	//Retorna la cuota disponible que le queda al usuario
	float cuotaDisponible(string datosJson);
	//Modifica la cuota asignada al usuario
	string modificarCuota(string datosJson,float cuotaNueva);
	//Retorna la lista de los hash de los archivos
	list<string> obtenerArchivos(string datosJson);
	virtual ~DatosDeUsuario();
private:
	//Puede ser privado
	string eliminar(string datosJson,string hashArchivo,string tipo,float espacio);
};

#endif /* DATOSDEUSUARIO_H_ */
