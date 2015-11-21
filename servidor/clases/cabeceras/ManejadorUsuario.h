#ifndef MANEJADORUSUARIO_H_
#define MANEJADORUSUARIO_H_

#include "Usuario.h"
#include "json/json.h"
#include "Respuesta.h"
#include "Log.h"

/**
 * Clase encargada de administrar usuarios,
 * segun lo recibido en el servidor
 */
class ManejadorUsuario {
private:
	Log * log;
public:
	ManejadorUsuario();
	/**
	* Genera un usuario, registrandolo en el sistema
	* @params nombreUsuario nombre del usuario a registrar en la base de datos.
	* @params datosUsuario datos del usuario a registrar en la base de datos.
	* @return Si el usuario ya existe, retorna un mensaje que el usuario no pudo ser creado
	*/
	string generar(const string &nombreUsuario,const string &datosUsuario);
	/**
	* Controla que el usuario exista, y la clave sea correcta
	* @params nombreUsuario nombre del usuario a iniciar sesion.
	* @params datosUsuario contiene la clave del usuario.
	* @return Si la clave o el usuario son incorrectos retorna un mensaje de error.
	*/
	string iniciarSesion(const string &nombreUsuario,const string &datosUsuario);
	/**
	* Obtiene los datos del usuario
	* @params nombreUsuario nombre del usuario del cual se quieren los datos.
	* @return  Retorna los metadatos del usuario.
	*/
	string obtenerDatos(const string &nombreUsuario);
	/**
	* Actualiza los datos del usuario
	* @params nombreUsuario nombre del usuario del cual se quieren actualizar los datos.
	* @params datosUsuario datos a actualizar.
	*/
	string actualizarDatos(const string &nombreUsuario,const string &datosUsuario);
	/**
	* Retorna los metadatos de los archivos que posee el usuario
	* @params nombreUsuario nombre del usuario del cual se quieren los metadatos de los archivos.
	*/
	string obtenerArchivos(const string &nombreUsuario);
	/**
	* Retorna los metadatos de los archivos que fueron compartidos con el usuairo
	* @params nombreUsuario nombre del usuario del cual se quieren los metadatos de los archivos.
	*/
	string obtenerArchivosCompartidos(const string &nombreUsuario);
	/**
	* Retorna los archivos que el usuairo posee en la papelera
	* @params nombreUsuario nombre del usuario del cual se quieren los metadatos de los archivos.
	*/
	string obtenerArchivosPapelera(const string &nombreUsuario);
	virtual ~ManejadorUsuario();
};

#endif /* MANEJADORUSUARIO_H_ */
