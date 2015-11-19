/*
 * Actualizador.h
 *
 *  Created on: 22 de oct. de 2015
 *      Author: mafv
 */

#ifndef ACTUALIZADOR_H_
#define ACTUALIZADOR_H_

#include <iostream>
#include "BaseDeDatos.h"
#include "Constantes.h"
#include "json/json.h"
#include "Hash.h"
#include "Usuario.h"
#include "ManejadorArchivosFisicos.h"
#include "Excepciones.h"
#include "Fecha.h"
#include "Log.h"

using namespace std;
using namespace Json;

/**
* Clase encargada de actualizar los metadatos del archivo
*/
class Actualizador {
private:
	Log *log;
	BasedeDatos *baseDeDatos;
	string propietario;
	string directorioOriginal;
	string nombreOriginal;
	string extensionOriginal;
	string nombreNuevo;
	string extensionNueva;
	string directorioNuevo;
	string fechaDeModificacion;
	string usuarioQueModifico;
	Value etiquetas;
	Value etiquetasNuevas;
	Value etiquetasEliminadas;
	bool cambionNombre;
	bool cambioExtension;
	bool cambioDirectorio;
	string nuevoHash;
	string antiguoHash;
	Value usuarios;
	Value datosAnteriores;
	unsigned int espacioNuevo;

public:
	Actualizador(const string &usuarioQueEstaModificando,const string &datosAActualizar);
	/**
	* Metodo encargado de actualizar el archivo
	*/
	string actualizarArchivo();
	virtual ~Actualizador();

private:
	void cargarDatos(const string &usuarioQueEstaModificando,const string &datosAActualizar);
	void actualizarHashAUsuarios();
	void actualizarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario);
	void eliminarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario);
	void actualizarEtiquetas();
	void actualizarEtiquetasNuevas();
	void actualizarEtiquetasEliminadas();
	void actualizarUsuariosCompartidos(const unsigned int &TIPO, const string &metadatoGuardar,const string &metadatoEliminar);
	string generarNuevoArchivo(const string &hashVersionPrevia);
	string generarAntiguoArchivo();
	string obtenerHahsPrevio();
	string convertirAString(const unsigned int &version);
	void actualizarArchivoFisico();
};

#endif /* ACTUALIZADOR_H_ */
