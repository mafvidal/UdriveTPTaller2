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
UsersController::UsersController(ManejadorDB* manejadorDB) {
	// TODO Auto-generated constructor stub
 this->manejadorDB = manejadorDB;
}

UsersController::~UsersController() {
	delete this->manejadorDB;
}

void UsersController::addUser(Request &request, StreamResponse &response)
{
	  if(  manejadorDB->registrarUsuario(request.getData())){
		  response << "Usuario creado exitosamente" << endl;
	  }else{
		  response << "Usuario existente" << endl;
	  }
}
void UsersController::setup()
{

	addRoute("POST","/users",UsersController, addUser);

}
void UsersController::CheckearBaseDeDatos(string ubicacion) {
	this->manejadorDB->CheckearBaseDeDatos("UsersController::CheckearBaseDeDatos");

}
}

