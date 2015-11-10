#include "Actualizador.h"

Actualizador::Actualizador(const string &usuarioQueEstaModificando,const string &datosAActualizar) {

	Reader lector;
	Hash hash;

	this->baseDeDatos = BasedeDatos::obteberInstancia();

	this->cargarDatos(usuarioQueEstaModificando,datosAActualizar);

	this->antiguoHash = hash.obtenerHashDelArchivo(this->propietario+this->directorioOriginal+this->nombreOriginal+this->extensionOriginal);

	if( this->antiguoHash == "" ){
		ArchivoInexistente e;
		throw e;
	}

	if(this->cambionNombre || this->cambioExtension || this->cambioDirectorio){

		this->nuevoHash = hash.obtenerHashNuevo(this->propietario+this->directorioNuevo+this->nombreNuevo+this->extensionNueva);

	}else{

		this->nuevoHash = this->antiguoHash;

	}

	lector.parse(this->baseDeDatos->leer(ARCHIVOS,this->antiguoHash),this->datosAnteriores);

	this->usuarios = this->datosAnteriores["Usuarios"];

}

string Actualizador::actualizarArchivo(){

	if(this->cambionNombre || this->cambioExtension || this->cambioDirectorio){

		this->actualizarHashAUsuarios();

		this->actualizarMetadato(NOMBRE,this->nombreNuevo,this->nuevoHash,this->propietario);
		this->eliminarMetadato(NOMBRE,this->nombreOriginal,this->antiguoHash,this->propietario);
		this->actualizarMetadato(EXTENSION,this->extensionNueva,this->nuevoHash,this->propietario);
		this->eliminarMetadato(EXTENSION,this->extensionOriginal,this->antiguoHash,this->propietario);
		this->actualizarMetadato(PROPIETARIO,this->propietario,this->nuevoHash,this->propietario);
		this->eliminarMetadato(PROPIETARIO,this->propietario,this->antiguoHash,this->propietario);

		this->actualizarUsuariosCompartidos(NOMBRE,this->nombreNuevo,this->nombreOriginal);
		this->actualizarUsuariosCompartidos(EXTENSION,this->extensionNueva,this->extensionOriginal);
		this->actualizarUsuariosCompartidos(PROPIETARIO,this->propietario,this->propietario);

		this->actualizarEtiquetas();

		this->actualizarArchivoFisico();

	}else if ( this->etiquetasNuevas.size() > 0 ){

		this->actualizarEtiquetasNuevas();

	}

	if ( this->etiquetasEliminadas.size() > 0 ){

		this->actualizarEtiquetasEliminadas();

	}

	const string &hashVersionPrevia = this->obtenerHahsPrevio();
	const string &nuevoArchivo = this->generarNuevoArchivo(hashVersionPrevia);
	const string &antiguoArchivo = this->generarAntiguoArchivo();

	this->baseDeDatos->eliminar(ARCHIVOS,this->antiguoHash);
	this->baseDeDatos->guardar(ARCHIVOS,hashVersionPrevia,antiguoArchivo);
	this->baseDeDatos->guardar(ARCHIVOS,this->nuevoHash,nuevoArchivo);

	return this->nuevoHash;

}

Actualizador::~Actualizador() {

}

void Actualizador::cargarDatos(const string &usuarioQueEstaModificando,const string &datosAActualizar){

	Reader lector;
	Value datos;
	Fecha fecha;

	lector.parse(datosAActualizar,datos,false);

	this->propietario = datos.get("Propietario","").asString();
	this->directorioOriginal = datos.get("DirectorioOriginal","").asString();
	this->nombreOriginal = datos.get("NombreOriginal","").asString();
	this->extensionOriginal = datos.get("ExtensionOriginal","").asString();
	this->nombreNuevo = datos.get("NombreNuevo","").asString();
	this->extensionNueva = datos.get("ExtensionNueva","").asString();
	this->directorioNuevo = datos.get("DirectorioNuevo","").asString();
	this->fechaDeModificacion = fecha.obtenerFecha();
	this->usuarioQueModifico = usuarioQueEstaModificando;
	this->espacioNuevo = datos.get("Espacio",0).asUInt();
	this->etiquetas = datos["Etiquetas"];
	this->etiquetasNuevas = datos["EtiquetasNuevas"];
	this->etiquetasEliminadas = datos["EtiquetasEliminadas"];

	this->cambionNombre = !(this->nombreOriginal == this->nombreNuevo);
	this->cambioExtension = !(this->extensionOriginal == this->extensionNueva);
	this->cambioDirectorio = !(this->directorioOriginal == this->directorioNuevo);

}


void Actualizador::actualizarHashAUsuarios(){

	Usuario usuario;

	usuario.eliminarArchivo(this->propietario,this->antiguoHash);
	usuario.agregarArchivo(this->propietario,this->nuevoHash);

	for ( unsigned int indice = 0; indice < this->usuarios.size(); ++indice ){

		const string nombreUsuario = this->usuarios[indice].asString();

		usuario.eliminarArchivoCompartido(nombreUsuario,this->antiguoHash);
		usuario.agregarArchivoCompartido(nombreUsuario,this->nuevoHash);

	}

}

void Actualizador::actualizarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario){

	Reader lector;
	Value datos;

	const string nombreMetadato = usuario + metadato;

	string datosMetadato = this->baseDeDatos->leer(TIPO,nombreMetadato);

	if ( datosMetadato != "" ){

		lector.parse(datosMetadato,datos,false);

	}

	//Verificar si fuciona si esta vacio
	datos["Archivos"].append(hashArchivo);

	this->baseDeDatos->guardar(TIPO,nombreMetadato,datos.toStyledString());

}

void Actualizador::eliminarMetadato(const unsigned int &TIPO, const string &metadato,const string &hashArchivo,const string &usuario){

	Reader lector;
	Value datos;
	Value archivosExistentes(arrayValue);
	Value archivos(arrayValue);

	const string nombreMetadato = usuario + metadato;

	string datosMetadato = this->baseDeDatos->leer(TIPO,nombreMetadato);

	lector.parse(datosMetadato,datos,false);

	archivosExistentes = datos["Archivos"];

	for ( unsigned int indice = 0; indice < archivosExistentes.size(); ++indice ){

		if(archivosExistentes[indice].asString() != hashArchivo ){

			archivos.append(Value(archivosExistentes[indice].asString()));

		}

	}

	if( archivos.size() == 0 ){

		this->baseDeDatos->eliminar(TIPO,nombreMetadato);

	}else{

		datos["Archivos"] = archivos;

		this->baseDeDatos->guardar(TIPO,nombreMetadato,datos.toStyledString());

	}

}

void Actualizador::actualizarUsuariosCompartidos(const unsigned int &TIPO,  const string &metadatoGuardar,const string &metadatoEliminar){

	for ( unsigned int indice = 0; indice < this->usuarios.size(); ++indice ){

		const string nombreUsuario = this->usuarios[indice].asString();

		this->actualizarMetadato(TIPO,metadatoGuardar,this->nuevoHash,nombreUsuario);
		this->eliminarMetadato(TIPO,metadatoEliminar,this->antiguoHash,nombreUsuario);

	}

}

void Actualizador::actualizarEtiquetas(){

	for ( unsigned int indice = 0; indice < this->etiquetas.size(); ++indice ){

		const string &etiqueta = this->etiquetas[indice].asString();

		this->actualizarMetadato(ETIQUETAS,etiqueta,this->nuevoHash,this->propietario);
		this->eliminarMetadato(ETIQUETAS,etiqueta,this->antiguoHash,this->propietario);

		this->actualizarUsuariosCompartidos(ETIQUETAS,etiqueta,etiqueta);

	}

}

void Actualizador::actualizarEtiquetasNuevas(){

	for ( unsigned int indice = 0; indice < this->etiquetasNuevas.size(); ++indice ){

		const string &etiqueta = this->etiquetasNuevas[indice].asString();

		this->actualizarMetadato(ETIQUETAS,etiqueta,this->nuevoHash,this->propietario);

		for ( unsigned int indice = 0; indice < this->usuarios.size(); ++indice ){

			const string &nombreUsuario = this->usuarios[indice].asString();

			this->actualizarMetadato(ETIQUETAS,etiqueta,this->nuevoHash,nombreUsuario);

		}

	}

}

void Actualizador::actualizarEtiquetasEliminadas(){

	for ( unsigned int indice = 0; indice < this->etiquetasEliminadas.size(); ++indice ){

		const string &etiqueta = this->etiquetasEliminadas[indice].asString();

		this->eliminarMetadato(ETIQUETAS,etiqueta,this->antiguoHash,this->propietario);

		for ( unsigned int indice = 0; indice < this->usuarios.size(); ++indice ){

			const string &nombreUsuario = this->usuarios[indice].asString();

			this->eliminarMetadato(ETIQUETAS,etiqueta,this->antiguoHash,nombreUsuario);

		}

	}

}

string Actualizador::generarNuevoArchivo(const string &hashVersionPrevia){

	Value nuevoArchivo;
	Value metadatos;

	nuevoArchivo["Usuarios"] = this->usuarios;
	metadatos["Propietario"] = this->propietario;
	metadatos["Nombre"] = this->nombreNuevo;
	metadatos["Extension"] = this->extensionNueva;
	metadatos["Directorio"] = this->directorioNuevo;
	metadatos["Etiquetas"] = this->etiquetas;
	metadatos["Version"] = this->datosAnteriores.get("Version",0).asUInt()+1;
	metadatos["UsuarioQueModifico"] = this->usuarioQueModifico;
	metadatos["FechaDeModificacion"] = this->fechaDeModificacion;
	nuevoArchivo["MetaDatos"] = metadatos;
	nuevoArchivo["Eliminado"] = false;
	nuevoArchivo["HashVersionAnterior"] = hashVersionPrevia;

	return nuevoArchivo.toStyledString();


}
string Actualizador::generarAntiguoArchivo(){

	Value antiguoArchivo;

	antiguoArchivo["Nombre"] = this->nombreOriginal;
	antiguoArchivo["Directorio"] = this->directorioOriginal;
	antiguoArchivo["Extension"] = this->extensionOriginal;
	//antiguoArchivo["UsuarioQueModifico"] = this->datosAnteriores.get("UsuarioQueModifico","").asString();
	//antiguoArchivo["FechaDeModificacion"] = this->datosAnteriores.get("FechaDeModificacion","").asString();
	antiguoArchivo["EtiquetasEliminadas"] = this->etiquetasEliminadas;
	antiguoArchivo["EtiquetasAgregadas"] = this->etiquetasNuevas;
	antiguoArchivo["Etiquetas"] = this->datosAnteriores["MetaDatos"]["Etiquetas"];
	antiguoArchivo["HashVersionAnterior"] = this->datosAnteriores.get("HashVersionAnterior","").asString();

	return antiguoArchivo.toStyledString();

}
string Actualizador::obtenerHahsPrevio(){

	Hash hash;

	const string &versionPrevia = this->convertirAString(this->datosAnteriores.get("Version",0).asUInt());
	return hash.obtenerHashNuevo(this->propietario+this->directorioOriginal+this->nombreOriginal+this->extensionOriginal+versionPrevia);

}

string Actualizador::convertirAString(const unsigned int &version){

	string versionString;
	ostringstream convertir;
	convertir << version;
	versionString = convertir.str();

	return versionString;

}

void Actualizador::actualizarArchivoFisico(){

	//ManejadorArchivosFisicos archivoFisico;

	string archivoOriginal = "./Udrive/"+this->antiguoHash;
	string archivoNuevo = "./Udrive/"+this->nuevoHash;

	rename(archivoOriginal.c_str(),archivoNuevo.c_str());

}

