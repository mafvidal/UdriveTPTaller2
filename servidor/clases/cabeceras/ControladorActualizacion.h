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

/**
* Clase encargada de controlar la actualizacion simultanea
* de un mismo archivo por mas de un cliente a la vez
*/
class ControladorActualizacion {
private:
	map<string,FILE*> archivos;
	mutex mtxVerificaActualizacion;
	mutex mtxArchivoActualizado;
	mutex mtxObtenerArchivo;

public:
	static ControladorActualizacion * obteberInstanciaControlador();
	/*
	* Marca que el archivo esta siendo actualizado
	* @params hashArchivo ID del archivo que se desea actualizar.
	* @params archivo archivo a actualizar.
	* @return retorna si otro usuario esta actualizando el mismo archivo
	*/
	bool seEstaActualizandoElArchivo(const string &hashArchivo,FILE * archivo);
	/*
	* Da por finalizada la actualizacion del archivo
	* @params hashArchivo ID del archivo que se desea actualizar.
	*/
	void archivoActualizado(const string &hashArchivo);
	/*
	* Metodo que retorna el archivo correspondiente al ID
	* @params hashArchivo ID del archivo que se desea actualizar.
	* @return retorna el archivo a actualizar
	*/
	FILE* obtenerArchivo(const string &hashArchivo);
	virtual ~ControladorActualizacion();
private:
	ControladorActualizacion();
	static void destruirInstanciaControlador();
	static ControladorActualizacion * unicaInstanciaControlador;
};

#endif /* CONTROLADORACTUALIZACION_H_ */
