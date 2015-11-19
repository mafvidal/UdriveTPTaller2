/*
 * Restaurador.h
 *
 *  Created on: 2 de nov. de 2015
 *      Author: mafv
 */

#ifndef RESTAURADOR_H_
#define RESTAURADOR_H_

#include <iostream>
#include "BaseDeDatos.h"
#include "Constantes.h"
#include "json/json.h"
#include "Hash.h"
#include "Usuario.h"
#include "Excepciones.h"
#include "Fecha.h"
#include "Log.h"

using namespace std;
using namespace Json;

class Restaurador {
private:
	Log *log;
	BasedeDatos *baseDeDatos;
	Value ultimaVersion;
	//La version que existe y voy a eliminar
	string hashVersionActual;
	//El hash para acceder a la version a restaurar
	string hashVersionPrevia;
	//El hash de la version que voy a restaurar
	string hashVersionARestaurar;
	//El hash de la version previa a la que voy a restaurar
	string hashVersionAnterior;
	string fechaDeModificacion;
	string usuarioQueModifico;
	string propietario;
	string nombre;
	string directorio;
	string extension;
	string nombreActual;
	string extensionActual;
	Value etiquetas;
	Value etiquetasAgregadas;
	Value etiquetasEliminadas;
	Value usuarios;

public:
	Restaurador(const string &usuarioQueRestaura,const string &datosARestaurar);
	string restaurarArchivo();
	unsigned int version();
	virtual ~Restaurador();
private:
	void cargarDatos(const string &usuarioQueRestaura,const string &datosARestaurar);
	void restaurarHashAUsuarios();
	void restaurarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario);
	void eliminarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario);
	void restaurarUsuariosCompartidos(const unsigned int &TIPO,  const string &metadatoGuardar,const string &metadatoEliminar);
	void restaurarEtiquetas();
	void eliminarEtiquetasAgregadas();
	string generarArchivo();
	void restaurarArchivoFisico();
};

#endif /* RESTAURADOR_H_ */