/*
 * UsersController.cpp
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */

#include "UsersController.h"
#include "BaseDeDatos.h"
#include <iostream>
#include <list>
#include "BaseDeDatos.h"
#include "estructuras.h"
#include <fstream>
#include "json/json.h"

namespace Mongoose
{

string cargarJsonUsuario(){

	//Cargo el json de prueba
	Json::Value datosUsuario;
	Json::Reader reader;
	ifstream test("datosDeUsuario.json", ifstream::binary);
	reader.parse( test, datosUsuario, false );

	return datosUsuario.toStyledString();

}

UsersController::UsersController() {
	// TODO Auto-generated constructor stub

}

UsersController::~UsersController() {
	// TODO Auto-generated destructor stub
}

void UsersController::addUser(Request &request, StreamResponse &response)
{

	string datosUsuario = cargarJsonUsuario();

	BaseDeDatos base("testdb/");
	base.agregarUsuario(htmlEntities(request.get("name")),"Clave",request.getData(),800);
	//bool agregarUsuario(string nombreUsuario,string clave,string metadatosJson,float cuota);
	if (base.existeUsuario(request.getData()))
		response << request.getData() << endl;

}
void UsersController::setup()
{

	addRoute("POST","/users",UsersController, addUser);

}
}

