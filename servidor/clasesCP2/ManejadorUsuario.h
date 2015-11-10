#ifndef MANEJADORUSUARIO_H_
#define MANEJADORUSUARIO_H_

#include "Usuario.h"
#include "json/json.h"
#include "Respuesta.h"

/*
 * Clase encargada de administrar usuarios,
 * segun lo recibido en el servidor
 *
 * */
class ManejadorUsuario {
public:
	ManejadorUsuario();
	//Genera un usuario, registrandolo en el sistema
	//Si el usuario ya existe, retorna un mensaje que el usuario no pudo ser creado
	string generar(const string &nombreUsuario,const string &datosUsuario);
	//Controla que el usuario exista, y la clave sea correcta
	string iniciarSesion(const string &nombreUsuario,const string &datosUsuario);
	string obtenerDatos(const string &nombreUsuario);
	string actualizarDatos(const string &nombreUsuario,const string &datosUsuario);
	string obtenerArchivos(const string &nombreUsuario);
	string obtenerArchivosPapelera(const string &nombreUsuario);
	virtual ~ManejadorUsuario();
};

#endif /* MANEJADORUSUARIO_H_ */
