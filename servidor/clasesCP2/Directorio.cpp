/*
 * Directorio.cpp
 *
 *  Created on: 8 de nov. de 2015
 *      Author: mafv
 */

#include "Directorio.h"

Directorio::Directorio() {
	// TODO Auto-generated constructor stub

}

void Directorio::crearDirectorioPrincipal(string directorioPrincipal){

	mkdir(directorioPrincipal.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
}

string Directorio::crearDirectorios(string directorios){

	istringstream iss(directorios);
	string directorio;
	string ruta="./Udrive/";

	for(unsigned int i = 0; getline(iss, directorio, '/') ; i++){
		if(directorio != "" ){
			ruta = ruta + directorio + "/";
			mkdir(ruta.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}

	}

	return ruta;

}

Directorio::~Directorio() {
	// TODO Auto-generated destructor stub
}

