/*
 * ControladorActualizacion.h
 *
 *  Created on: 11 de nov. de 2015
 *      Author: mafv
 */

#ifndef CONTROLADORACTUALIZACION_H_
#define CONTROLADORACTUALIZACION_H_

#include <iostream>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <mutex>

using namespace std;

class ControladorActualizacion {
private:
	map<string,FILE*> archivos;
	mutex mtxVerificaActualizacion;
	mutex mtxArchivoActualizado;
	mutex mtxObtenerArchivo;

public:
	static ControladorActualizacion * obteberInstanciaControlador();
	bool seEstaActualizandoElArchivo(const string &hashArchivo,FILE * archivo);
	void archivoActualizado(const string &hashArchivo);
	FILE* obtenerArchivo(const string &hashArchivo);
	virtual ~ControladorActualizacion();
private:
	ControladorActualizacion();
	static void destruirInstanciaControlador();
	static ControladorActualizacion * unicaInstanciaControlador;
};

#endif /* CONTROLADORACTUALIZACION_H_ */
