#include "../cabeceras/Buscador.h"

Buscador::Buscador() {

	this->baseDeDatos = BasedeDatos::obteberInstancia();
	this->log = Log::obteberInstanciaLog();

}
string Buscador::buscarPorEtiqueta(const string &usuario,const string &etiqueta){

	return this->buscarMetadato(ETIQUETAS,usuario+etiqueta);

}
string Buscador::buscarPorPropietario(const string &usuario,const string &propietario){

	return this->buscarMetadato(PROPIETARIO,usuario+propietario);

}
string Buscador::buscarPorNombre(const string &usuario,const string &nombre){

	return this->buscarMetadato(NOMBRE,usuario+nombre);

}
string Buscador::buscarPorExtension(const string &usuario,const string &extension){

	return this->buscarMetadato(EXTENSION,usuario+extension);

}


Buscador::~Buscador() {
}
string Buscador::buscarMetadato(const unsigned int &TIPO,const string &metadato){

	Value hashArchivos;
	Value datosArchivos;
	Value archivosMetadatos(arrayValue);
	Reader lector;
	Archivo archivo;

	lector.parse(this->baseDeDatos->leer(TIPO,metadato),hashArchivos,false);

	Value archivos(arrayValue);
	archivos = hashArchivos["Archivos"];

	for ( unsigned int indice = 0; indice < archivos.size(); ++indice ){

		const string hash = archivos[indice].asString();

		this->log->debug("Agregado el archivo: "+hash+" a la busqueda");

		Value datos = this->obtenerDatos(hash);

		if ( datos == nullValue )
			continue;

		archivosMetadatos.append(datos);

	}

	return archivosMetadatos.toStyledString();

}

Value Buscador::obtenerDatos(const string & hashDelArchivo){

	Value datos;
	Value metadatos;
	Value metadatosNuevos;
	Reader lector;

	const string &datosDelArchivo = this->baseDeDatos->leer(ARCHIVOS,hashDelArchivo);

	lector.parse(datosDelArchivo,datos);

	if( datos.get("Eliminado",false).asBool() )
		return nullValue;

	metadatos = datos["MetaDatos"];

	metadatosNuevos["Propietario"] = metadatos.get("Propietario","").asString();
	metadatosNuevos["Nombre"] = metadatos.get("Nombre","").asString();
	metadatosNuevos["Extension"] = metadatos.get("Extension","").asString();
	metadatosNuevos["Directorio"] = metadatos.get("Directorio","").asString();
	metadatosNuevos["Version"] = metadatos.get("Version",0).asUInt();
	metadatosNuevos["Etiquetas"] = metadatos["Etiquetas"];
	metadatosNuevos["UsuarioQueModifico"] = metadatos.get("UsuarioQueModifico","").asString();
	metadatosNuevos["FechaDeModificacion"] = metadatos.get("FechaDeModificacion","").asString();
	metadatosNuevos["ID"] = hashDelArchivo;

	return metadatosNuevos;

}
