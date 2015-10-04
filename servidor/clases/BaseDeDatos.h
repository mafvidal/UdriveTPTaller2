#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <iostream>
#include <sstream>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include <vector>
#include <assert.h>
#include <list>
#include <mutex>
#include "estructuras.h"
#include "DatosDeUsuario.h"
#include "DatosDeArchivos.h"
#include "MetadatosConsulta.h"

using namespace std;
using namespace rocksdb;


class BaseDeDatos {
private:
	mutex mtx;
	const int USARIOS=1;
	const int ARCHIVOS=2;
	const int ETIQUETAS=3;
	const int NOMBRE=4;
	const int EXTENSION=5;
	const int PROPIETARIO=6;
	DB* db;
	Status estado;
	string dirPath;
	vector<ColumnFamilyHandle*> handles;

public:
	BaseDeDatos(string directorio);
	//Agrega un usuario nuevo a la base de datos
	//El usuario no debe existir
	bool agregarUsuario(string nombreUsuario,string clave,string metadatosJson,float cuota);
	//Retorna si el usuario existe o no en la base de datos
	bool existeUsuario(string nombreUsuario);
	//Devuelve si la clave es la del usuario
	//El usuario debe existir
	bool esLaClaveCorrecta(string nombreUsuario,string clave);
	//Devuelve los metadatos del usuario
	//el usuario debe existir
	string getMetaDatosUsuario(string nombreUsuario);
	//Almacena los metaDatos de un usuario
	//Los datos son reemplazados
	bool setDatosUsuario(string nombreUsuario, string metaDatosUsuario);
	//Agregar el nombre del archivo en el directorio
	//El usuario debe existir
	bool agregarArchivo(string nombreUsuario,string metadatos,float espacio);
	//Devuelve la lista de archivos que posee el usuario
	list<string> getArchivos(string nombreUsuario);
	//Elimina logicamente el archivo de la base de datos
	void eliminarLogicamenteArchivo(string nombreUsuario,string metadatosArchivo,float espacio);
	//Elimina fisicamente el archivo de la base de datos
	void eliminarFisicamenteArchivo(string nombreUsuario,string metadatosArchivo);
	//Devuelve la lista de archivos que posee el usuario en la papelera
	list<string> getArchivosEnPapelera(string nombreUsuario);
	//Devuelve la lista de archivos que coinciden con la etiqueta del usuario
	list<string> buscarPorEtiquetas(string nombreUsuario,string etiqueta);
	//Devuelve la lista de archivos que coinciden con la etiqueta del usuario
	list<string> buscarPorExtension(string nombreUsuario,string extension);
	//Devuelve la lista de archivos que coinciden con la etiqueta del usuario
	list<string> buscarPorNombre(string nombreUsuario,string nombre);
	//Devuelve la lista de archivos que coinciden con la etiqueta del usuario
	list<string> buscarPorPropietario(string nombreUsuario,string propietario);
	//Retorna la cuota que tiene disponible el usuario
	float cuotaDisponible(string nombreUsuario);

	~BaseDeDatos();
private:

	unsigned int obtenerHash(string archivo);
	void inicializarColumnas();
	void cargarColumnas();
	string convertirAString(unsigned int hash);
	list<string> obtenerArchivos(string nombreUsuario,string modo);
	void cargarEtiquetas(list<string> etiquetas, string nombreUsuario,string hashArchivo);
	void cargarMetadatos(string metadato, string nombreUsuario,string hashArchivo,const int TIPO);
	list<string> buscarPorMetadato(string nombreUsuario,string propietario,const int TIPO);
	bool escribir(const int TIPO,string nombre,string datos);
	void eliminar(const int TIPO,string nombre);

};

#endif /* BASEDEDATOS_H_ */
