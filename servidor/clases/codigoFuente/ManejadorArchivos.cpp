#include "../cabeceras/ManejadorArchivos.h"

ManejadorArchivos::ManejadorArchivos() {

	this->log = Log::obteberInstanciaLog();

}

string ManejadorArchivos::crearArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		string hashArchivo = archivo.crearArchivo(nombreUsuario,datosDelArchivo);

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje(hashArchivo);

		this->log->debug("Se guardaron correctamente los metadatos del archivo: "+hashArchivo);

	}catch (ELimiteDeCuota &l){

		this->log->debug("No se pudieron guardar los metadatos del archivo");
		this->log->warn("No se guardan los metadatos del archivo, ya que se supera la cuota del usuario");

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo supera el limite de cuota");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::eliminarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		const string &resultado = archivo.eliminarArchivo(nombreUsuario,datosDelArchivo);

		if( resultado == "OK" ){

			respuesta.agregarEstado("OK");
			respuesta.agregarMensaje("Archivo enviado a la papelera");

			this->log->debug("Se envio el archivo a la papelera");

		}else if ( resultado == "NoEsPropietario" ){

			respuesta.agregarEstado("ERROR");
			respuesta.agregarMensaje("Solo el propietario puede eliminar el archivo");

			this->log->debug("No se pudo eliminar el archivo");
			this->log->warn("El usuario: "+nombreUsuario+" no puede eliminar archivos de los que no es propietario");

		}

	}catch(EArchivoYaEliminado &e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo ya se encuentra en la papelera");

		this->log->debug("No se pudo eliminar el archivo");
		this->log->warn("Se quiere enviar a la papelera un archivo que ya se encuentra en la papelera");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::compartirArchivo(const string &datosDelArchivo){

	Archivo archivo;
	Value usuarios;
	Value datos;
	Reader lector;
	Respuesta respuesta;

	lector.parse(datosDelArchivo,datos);

	usuarios = datos["Usuarios"];

	string resultado = archivo.compartir(usuarios.toStyledString(),datosDelArchivo);

	if( resultado == "OK" ){

		respuesta.agregarEstado("OK");
		respuesta.agregarMensaje("El archivo fue compartido");

		this->log->debug("El archivo fue compartido existosamente");

	}else if ( resultado == "" ){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo a compartir no existe");

		this->log->debug("El archivo no pudo ser compartido");
		this->log->warn("El archivo a compartir no existe");

	}else{

		respuesta.agregarEstado("WARNIG");
		respuesta.agregarMensaje("Los ususarios: "+resultado+" no existen");

		this->log->debug("El archivo fue compartido existosamente");

	}


	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::actualizarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		string hashArchivo = archivo.actualizar(nombreUsuario,datosDelArchivo);

		if( hashArchivo != "" ){

			respuesta.agregarEstado("OK");
			respuesta.agregarMensaje(hashArchivo);

			this->log->debug("El archivo: "+hashArchivo+" fue actualizado existosamente");

		}

	}catch (EArchivoInexistente &e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("No existe el archivo a actualizar");

		this->log->debug("El archivo no se pudo actualizar");
		this->log->warn("El archivo a actualizar no existe");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::restaurarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		const string &resultado = archivo.restaurar(nombreUsuario,datosDelArchivo);

		if( resultado != "Version0" ){

			respuesta.agregarEstado("OK");
			respuesta.agregarMensaje(resultado);

			this->log->debug("Se restauro el archivo a la vesion anterior");

		}else {

			respuesta.agregarEstado("ERROR");
			respuesta.agregarMensaje("No existe una version del archivo a restaurar");

			this->log->debug("No se pudo restaurar el archivo");
			this->log->warn("No existe una version previa del archivo");

		}


	}catch(EArchivoInexistente &e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo a restaurar no existe");

		this->log->debug("No se pudo restaurar el archivo");
		this->log->warn("El archivo a restaurar no existe");

	}

	return respuesta.obtenerRespuesta();

}

string ManejadorArchivos::recuperarArchivo(const string &nombreUsuario,const string &datosDelArchivo){

	Respuesta respuesta;
	Archivo archivo;

	try{

		if( archivo.recuperarArchivo(nombreUsuario,datosDelArchivo) ){

			respuesta.agregarEstado("OK");
			respuesta.agregarMensaje("Archivo recuperado");

			this->log->debug("Se recupero el archivo de la papelera");

		}else{

			respuesta.agregarEstado("ERROR");
			respuesta.agregarMensaje("No dispone de espacio suficiente para restaurar el archivo");

			this->log->debug("No se pudo recuperar el archivo de la papelera");
			this->log->warn("No se dispone de la cuota suficiente para recuperar el archivo de la papelera");

		}

	} catch(EArchivoExistente &e){

		respuesta.agregarEstado("ERROR");
		respuesta.agregarMensaje("El archivo no fue eliminado");

		this->log->debug("No se pudo recuperar el archivo de la papelera");
		this->log->warn("El archivo no se encuentra en la papelera");


	}

	return respuesta.obtenerRespuesta();

}

ManejadorArchivos::~ManejadorArchivos() {
}

