#ifndef USUARIO_H_
#define USUARIO_H_

#include "BaseDeDatos.h"
#include "json/json.h"
#include "Constantes.h"
#include <iostream>
#include "Archivo.h"
#include "Log.h"

using namespace Json;
using namespace std;

/**
* Esta clase es la encargada de administrar 
* los datos del usuario en la base de datos
*/
class Usuario {
private:
	Log *log;
	BasedeDatos *baseDeDatos;
public:
	Usuario();
	/**
	* Verifica si el usuario y la clave son correctas
	* @param usuario nombre del usuario que desea identificarse
	* @param json contiene la clave del usuario a identificarse
	* @return retornar si el usuario pudo o no identificarse 
	* con la clave y nombre de usuario
	*/
	bool identificarse(const string &usuario,const string &json);
	/**
	* Registra al usuario en la base de datos
	* @param usuario nombre del usuario que desea registrase
	* @param json contiene los datos del usuario
	* @return retornar si el usuario pudo o no registrarse
	*/
	bool registrarse(const string &usuario,const string &json);
	/**
	* Permite obtener los metadatos de un usuario
	* @param usuario nombre del usuario del que se desea obtener sus metadatos
	* @return retorna los metadatos del usuario
	*/
	string obtenerDatos(const string &usuario);
	/**
	* Actualiza los datos del usuario; clave, cuota, metadatos
	* @param usuario nombre del usuario que se desea actualizar sus datos
	* @param json contiene los datos del usuario a actualizar
	* @return retornar si se pudieron actualizar los datos correctamente
	*/
	bool actualizarDatos(const string &usuario,const string & json);
	/**
	* Permite obtener los archivos que posee el usuario
	* @param usuario nombre del usuario del que se desean obtener los archivos
	* @return retornar la lista de archivos que posee el usuario
	*/
	string obtenerArchivos(const string & usuario);
	/**
	* Permite obtener los archivos que fueron compartidos con el usuario
	* @param usuario nombre del usuario del que se desean obtener los archivos
	* @return retornar la lista de archivos compartidos con el usuario
	*/
	string obtenerArchivosCompartidos(const string & usuario);
	/**
	* Permite obtener los archivos que se encuentran en la papelera
	* @param usuario nombre del usuario del que se desean obtener los archivos
	* @return retornar la lista de archivos que se encuentran en la papelera
	*/
	string verPapelera(const string &usuario);
	void eliminarArchivoCompartido(const string &usuario,const string &hashArchivo);
	void agregarArchivoCompartido(const string &usuario,const string &hashArchivo);
	void eliminarArchivo(const string &usuario,const string &hashArchivo);
	void agregarArchivo(const string &usuario,const string &hashArchivo);
	void enviarALaPapelera(const string &nombreUsuario,const string &hashArchivo);
	/**
	* Permite verificar si un usuario se encuentra en la base de datos
	* @param usuario nombre del usuario del que se desea verificar si esta en la base de datos
	* @return Retorna si el usuario se encuentra o no almacenado en la base de datos
	*/
	bool existeUsuario(const string &nombreUsuario);
	/**
	* Permite sacar un archivo de la papelera
	* @param usuario nombre del usuario del que se recuperar el archivo
	* @param hashArchivo ID del archivo a sacar de la papelera
	* @return Retorna si el usuario se encuentra o no almacenado en la base de datos
	*/
	void sacarDeLaPapelera(const string &nombreUsuario,const string &hashArchivo);
	/**
	* Aumenta la cuota usada por el usuario
	* @param usuario nombre del usuario del que se quiere aumentar la cuota usada
	* @param cuotaUsada valor a aumentar
	* @return Si la cuota no se puede aumenta ya que es mayor que el tope retorna false
	*/
	bool aumentarCuotaUsada(const string &nombreUsuario,const unsigned int cuotaUsada);
	/**
	* Disminuye la cuota usada por el usuario, segun el valor recibido
	* @param usuario nombre del usuario del que se quiere disminuir la cuota usada
	* @param cuotaUsada valor a disminuir
	*/
	void disminuirCuotaUsada(const string &nombreUsuario,const unsigned int cuotaUsada);
	/**
	* Permite conocer la cuota que el usuario dispone
	* @param usuario nombre del usuario del que se quiere conocer la cuota disponible
	* @return retorna el valor de la cuota que el usuario tiene diponible
	*/
	unsigned int obtenerCuotaDisponible(const string &nombreUsuario);
	virtual ~Usuario();
private:
	Value cargarMetadatos(const Value &metadatos);
	void cargarArchivos(Value &archivos,const Value &archivosExistentes);
	void eliminar(const string &usuario,const string &hashArchivo,const string &tipo);
	void agregar(const string &usuario,const string &hashArchivo,const string &tipo);
	Value getMetadatosArchivo(const Value &metadatos);
};

#endif /* USUARIO_H_ */
