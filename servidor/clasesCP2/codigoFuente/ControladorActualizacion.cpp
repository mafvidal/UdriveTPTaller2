#include "../cabeceras/ControladorActualizacion.h"

ControladorActualizacion* ControladorActualizacion::unicaInstanciaControlador = NULL;

ControladorActualizacion * ControladorActualizacion::obteberInstanciaControlador(){

	if( unicaInstanciaControlador == NULL ){
		unicaInstanciaControlador = new ControladorActualizacion();
		atexit(&destruirInstanciaControlador);
	}
	return unicaInstanciaControlador;

}

bool ControladorActualizacion::seEstaActualizandoElArchivo(const string &hashArchivo,FILE * archivo){

	this->mtxVerificaActualizacion.lock();
	if( this->archivos.find(hashArchivo) == this->archivos.end() ){

		this->archivos[hashArchivo] = archivo;
		this->mtxVerificaActualizacion.unlock();
		return false;

	}else{
		this->mtxVerificaActualizacion.unlock();
		return true;

	}

}

void ControladorActualizacion::archivoActualizado(const string &hashArchivo){

	this->mtxArchivoActualizado.lock();
	this->archivos.erase(hashArchivo);
	this->mtxArchivoActualizado.unlock();

}

FILE* ControladorActualizacion::obtenerArchivo(const string &hashArchivo){

	this->mtxObtenerArchivo.lock();
	FILE * archivo = this->archivos[hashArchivo];
	this->mtxObtenerArchivo.unlock();
	return archivo;

}

ControladorActualizacion::~ControladorActualizacion() {
}

//Metodos privados

ControladorActualizacion::ControladorActualizacion() {

}

void ControladorActualizacion::destruirInstanciaControlador(){
	if(unicaInstanciaControlador != NULL)
		delete unicaInstanciaControlador;
}
