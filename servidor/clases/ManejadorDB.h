#ifndef MANEJADORDB_H_
#define MANEJADORDB_H_

#include <string>
#include <list>
#include "json/json.h"
#include "BaseDeDatos.h"
#include <fstream>

using namespace std;
using namespace Json;

class ManejadorDB {
private:
	BaseDeDatos *db;
public:
	void CheckearBaseDeDatos(string ubicacion){
		this->db->CheckearBaseDeDatos(ubicacion);
	}
	ManejadorDB(BaseDeDatos * db);
	//Registra el usuario en la base de datos
	//Retorna si pudo o no agregarlo
	bool registrarUsuario(string registroJson);
	//Inicia sesion de un usuario
	//Retorna si se pudo o no iniciar sesion
	bool iniciarsesion(string sesionJson);
	//Agrega el archivo a la base de datos
	//Retorna si se pudo o no agregar el archivo
	bool agregarArchivo(string archivoJson);
	//Retorna la lista de archivos
	//Si no tiene retorna la lista vacia
	string obtenerListaArchivos(string usuarioJson);
	//Elimina un archivo logicamente
	void eliminarArchivo(string archivoJson);
	//Retorna los archivos de la papelera
	string verPapelera(string usuarioJson);
	//Elimina el archivo de la papelera
	void eliminarArchivoDePapelera(string archivoJson);
	~ManejadorDB();

};

#endif /* MANEJADORDB_H_ */
