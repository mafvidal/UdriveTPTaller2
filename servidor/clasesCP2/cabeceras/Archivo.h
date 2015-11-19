#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include "BaseDeDatos.h"
#include "json/json.h"
#include "Constantes.h"
#include "Actualizador.h"
#include "Restaurador.h"
#include "Hash.h"
#include "Usuario.h"
#include "Log.h"
#include <iostream>

using namespace Json;
using namespace std;

/**
* Clase que permite almacenar archivos
* los metadatos en la base de datos
*/
class Archivo {
private:
	BasedeDatos *baseDeDatos;
	Log *log;
public:
	Archivo();
	/**
	* Almacena en la base de datos, los metadatos del archivo
	* El archivo es agregado por primera vez a la base de datos
	* @params usuario propietario del archivo.
	* @params json datos del archivo.
	*/
	string crearArchivo(const string &usuario,const string &json);
	/**
	* El archivo es agregado por primera vez a la base de datos
	* @params usuario propietario del archivo, que elimina.
	* @params json datos del archivo.
	*/
	string eliminarArchivo(const string &nombreUsuarioEliminador,const string &json);
	/**
	* Retorna los datos del archivo
	* @params hashDelArchivo id del archivo que se quieren los datos.
	*/
	Value obtenerDatos(const string & hashDelArchivo);
	/**
	* Comparte el archivo segun el json, con los usuariosACompartir
	* @params usuariosACompartir usuarios con lo que se desea compartir el archivo.
	* @params json datos del archivo a compartir.
	*/
	string compartir(const string &usuariosACompartir,const string & json);
	/**
	* Actualiza el archivo
	* @params nombreUsuario usuarios que realiza la actualizacion.
	* @params json datos del archivo a actualizar.
	*/
	string actualizar(const string & nombreUsuario,const string & json);
	/**
	* Restaura el archivo
	* @params nombreUsuario usuarios que realiza la restauracion del archivo.
	* @params json datos del archivo a restaurar.
	*/
	string restaurar(const string & nombreUsuario,const string & json);
	/**
	* Recupera el archivo de la papelera
	* @params nombreUsuario usuarios que recupera el archivo de la papelera.
	* @params json datos del archivo a recuperar.
	*/
	bool recuperarArchivo(const string &nombreUsuarioRecuperador,const string &json);
	virtual ~Archivo();
private:
	void guardarMetadatosAUsuarios(const string &usuario,const Value &datos,const string &hash);
	void guardarMetadato(const unsigned int &TIPO,const string &usuario,const string &metadato,const string & hashArchivo);
	string obtenerMetadatos(const Value &metadatos);
	string convertirAString(const unsigned int &valor);
};

#endif /* ARCHIVO_H_ */
