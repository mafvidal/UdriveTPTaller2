#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include "BaseDeDatos.h"
#include "json/json.h"
#include "Constantes.h"
#include "Actualizador.h"
#include "Restaurador.h"
#include "Hash.h"
#include "Usuario.h"
#include <iostream>

using namespace Json;
using namespace std;

class Archivo {
private:
	BasedeDatos *baseDeDatos;
public:
	Archivo();
	//Almacena en la base de datos, los metadatos del archivo
	//El archivo es agregado por primera vez a la base de datos
	//Retorna si se pudo o no guardar el archivo
	string crearArchivo(const string &usuario,const string &json);
	//Elimina el archivo enviandolo a la papelera
	//Recibe los datos del archivo
	string eliminarArchivo(const string &nombreUsuarioEliminador,const string &json);
	Value obtenerDatos(const string & hashDelArchivo);
	//Comparte el archivo segun el json, con los usuariosACompartir
	string compartir(const string &usuariosACompartir,const string & json);
	string actualizar(const string & nombreUsuario,const string & json);
	string restaurar(const string & nombreUsuario,const string & json);
	bool recuperarArchivo(const string &nombreUsuarioRecuperador,const string &json);
	virtual ~Archivo();
private:
	void guardarMetadatosAUsuarios(const string &usuario,const Value &datos,const string &hash);
	void guardarMetadato(const unsigned int &TIPO,const string &usuario,const string &metadato,const string & hashArchivo);
	string obtenerMetadatos(const Value &metadatos);
	string convertirAString(const unsigned int &valor);
};

#endif /* ARCHIVO_H_ */
