/*
 * AdministradorServidor.cpp
 *
 *  Created on: 3 de nov. de 2015
 *      Author: mafv
 */

#include "AdministradorServidor.h"

AdministradorServidor::AdministradorServidor(struct mg_connection *c, int ev, struct http_message p) {

	this->c = c;
	this->ev = ev;
	this->hm = p;
	this->log = Log::obteberInstanciaLog();

}

void AdministradorServidor::administrar(){

	struct datosArchivo *datos = (struct datosArchivo *) this->c->user_data;

	if( datos == NULL ){

		if ( ev == MG_EV_RECV ) {

			int req_len = mg_parse_http(this->c->recv_mbuf.buf, this->c->recv_mbuf.len, &hm,1);

			if (req_len < 0 || (req_len == 0 && c->recv_mbuf.len >= MG_MAX_HTTP_REQUEST_SIZE)) {

				c->flags |= MG_F_CLOSE_IMMEDIATELY;

			} else if (req_len == 0) {

			}else{

				this->parsearMensaje();

				this->log->info("Procesando solicitud del cliente");

				//Crea el archivo
				if( mensaje.archivoFisico == "POSTusuariosarchivofisico" ){

					this->log->debug("Creando archivo");

					try{

						ManejadorArchivosFisicos archivoFisico(mensaje.hashArchivo);

						archivoFisico.crearArchivoFisico(c,hm);

						this->administrar();

					}catch ( EArchivoInexistente &e ){

						this->log->warn("El archivo solicitado no existe");

						this->cerrar();

					}
				//Actualiza el archivo
				}else if( mensaje.archivoFisico == "PUTusuariosarchivofisico" ){

					this->log->debug("Actualizando archivo");

					try{

						ManejadorArchivosFisicos archivoFisico(mensaje.hashArchivo);

						archivoFisico.actualizarArchivoFisico(c,hm);

						this->administrar();

					}catch ( EArchivoInexistente &e ){

						this->log->warn("El archivo solicitado no existe");

						this->cerrar();

					}
				//Guarda el la foto del usuario
				}else if( mensaje.archivoFisico == "POSTusuariosfoto" ){

					this->log->debug("Cargar foto del usuario");

					try{

						ManejadorArchivosFisicos archivoFisico;

						archivoFisico.guardarFoto(c,hm,mensaje.quien);

						this->administrar();

					}catch ( EUsuarioInexistente &e ){

						this->log->warn("El usuario no existe: "+mensaje.quien);

						Respuesta respuesta;
						respuesta.agregarEstado("ERROR");
						respuesta.agregarMensaje("El Usuario no existe");

						const string &error=respuesta.obtenerRespuesta();

						mg_printf(c, "HTTP/1.0 200 OK\r\nContent-Length: %d\r\n"
									"Content-Type: application/json\r\n\r\n%s",
									(int) error.size(), error.c_str());

					}

				}

			}

		}else if ( this->ev == MG_EV_HTTP_REQUEST ){

			this->parsearMensaje();

			this->log->info("Procesando solicitud del cliente");

			//Se solicita un archivo
			if ( mensaje.archivoFisico == "GETusuariosarchivofisico" ){

				this->log->debug("Solicitud de archivo");

				ManejadorArchivosFisicos archivoFisico;

				archivoFisico.enviarArchivo(c,mensaje.hashArchivo,mensaje.version);

			//Se solicita la foto del usuario
			}else if ( mensaje.archivoFisico == "GETusuariosfoto" ){

				this->log->debug("Solicitud de foto");

				ManejadorArchivosFisicos archivoFisico;

				archivoFisico.enviarArchivo(c,mensaje.quien,-1);

			}else{

				string respuesta = this->realizarOperacion();
				mg_printf(c, "HTTP/1.0 200 OK\r\nContent-Length: %d\r\n"
								"Content-Type: application/json\r\n\r\n%s",
								(int) respuesta.size(), respuesta.c_str());

			}

		}

	}else if ( this->ev == MG_EV_RECV ){

		ManejadorArchivosFisicos archivoFisico;

		archivoFisico.cargarArchivo(c);

	}

}

AdministradorServidor::~AdministradorServidor() {
}


int AdministradorServidor::sonIguales(const struct mg_str *s1, const struct mg_str *s2){

	return s1->len == s2->len && memcmp(s1->p, s2->p, s2->len) == 0;

}
void AdministradorServidor::parsearMensaje(){

	string URL;
	for(size_t i=0;i<hm.uri.len;i++){
		URL = URL+ hm.uri.p[i];
	}

	this->log->debug("URL: "+URL);

	string tipo = "";
	string nombreUsuario = "";
	string archivos = "";
	string operacion = "";
	string metadato = "";
	string hashArchivo = "";
	int version = -1;

	istringstream iss(URL);
	string palabra;

	for(unsigned int i = 0; getline(iss, palabra, '/') ; i++){
		if(i==1){
			tipo = this->determinarProtocolo()+palabra;
		}else if(i==2){
			nombreUsuario = palabra;
		}else if(i==3){
			archivos = palabra;
		}else if(i==4){
			hashArchivo = palabra;
			operacion = palabra;
		}else if(i==5){
			metadato = palabra;
			if( archivos == "archivofisico" )
				version = atoi( palabra.c_str() );
		}

	}

	mensaje.quien = nombreUsuario;
	mensaje.tipo = tipo+archivos+operacion;
	mensaje.metadato = metadato;
	mensaje.archivoFisico = tipo+archivos;//+metadato;
	mensaje.hashArchivo = hashArchivo;
	mensaje.version = version;

}

string AdministradorServidor::determinarProtocolo(){

	if (this->sonIguales(&hm.method, &s_put_method)){
		this->log->debug("Tipo de operacion: PUT");
		return "PUT";

	}else if(this->sonIguales(&hm.method, &s_get_method)){
		this->log->debug("Tipo de operacion: GET");
		return "GET";

	}else if(this->sonIguales(&hm.method, &s_post_method)){
		this->log->debug("Tipo de operacion: POST");
		return "POST";

	}else if(this->sonIguales(&hm.method, &s_delele_method)){
		this->log->debug("Tipo de operacion: DELETE");
		return "DELETE";

	}else{
		this->log->warn("Tipo de operacion inexistente");
		return "ERROR";

	}

}

string AdministradorServidor::realizarOperacion(){

	string respuesta;
	string cuerpo = hm.body.p;

	this->log->info("Procesando solicitud del cliente");

	//Verifico que el usuario que solicita exista
	Usuario usuario;
	if( (mensaje.tipo != "POSTusuarios") && (!usuario.existeUsuario(mensaje.quien)) ){

		this->log->warn("Usuario inexistente: "+mensaje.quien);

		Respuesta error;
		error.agregarEstado("ERROR");
		error.agregarMensaje("El usuario no existe");

		return error.obtenerRespuesta();

	}

	//Registrar usuario
	if(mensaje.tipo == "POSTusuarios"){

		this->log->debug("Registrando nuevo usuario");

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.generar(mensaje.quien,cuerpo);

	//Iniciar sesion del usuario
	}else if(mensaje.tipo == "POSTiniciarsesion"){

		this->log->debug("Inicio de sesion");

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.iniciarSesion(mensaje.quien,cuerpo);

	//retorna los datos del usuario, email,nombre,ubicacion,foto
	}else if(mensaje.tipo == "GETusuarios"){

		this->log->debug("Solicitud de datos del usuario");

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.obtenerDatos(mensaje.quien);

	//actualiza los datos del usuario, email,nombre,ubicacion,foto
	}else if(mensaje.tipo == "PUTusuarios"){

		this->log->debug("Actualizacion de datos del usuario");

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.actualizarDatos(mensaje.quien,cuerpo);

	//Retorna los datos de los archivos que posee el usuario, solo los propios,
	}else if(mensaje.tipo == "GETusuariosarchivos"){

		this->log->debug("Solicitud de metadatos de los archivos del usuario");

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.obtenerArchivos(mensaje.quien);

	//Retorna los datos de los archivos que fueron compartidos con el usuario
	}else if(mensaje.tipo == "GETusuariosarchivoscompartidos"){

		this->log->debug("Solicitud de metadatos de los archivos compartidos con el usuario");

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.obtenerArchivosCompartidos(mensaje.quien);

	}else if(mensaje.tipo == "DELETEusuariosarchivos"){

		this->log->debug("Eliminando archivos");

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.eliminarArchivo(mensaje.quien,cuerpo);

	//Crea el archivo logico
	}else if(mensaje.tipo == "POSTusuariosarchivos"){

		this->log->debug("Cargando metadatos de nuevo archivo");

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.crearArchivo(mensaje.quien,cuerpo);

	//Comparte el archivo recibido con los usuarios recibidos
	}else if(mensaje.tipo == "PUTusuariosarchivoscompartir"){

		this->log->debug("Compartiendo archivo");

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.compartirArchivo(cuerpo);

	}else if(mensaje.tipo == "GETusuariosarchivosetiquetas"){

		this->log->debug("Buscando archivos por etiquetas");

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorEtiquetas(mensaje.quien,mensaje.metadato);

	}else if(mensaje.tipo == "GETusuariosarchivosnombre"){

		this->log->debug("Buscando archivos por nombre");

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorNombre(mensaje.quien,mensaje.metadato);

	}else if(mensaje.tipo == "GETusuariosarchivospropietario"){

		this->log->debug("Buscando archivos por propietario");

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorPropietario(mensaje.quien,mensaje.metadato);

	}else if(mensaje.tipo == "GETusuariosarchivosextension"){

		this->log->debug("Buscando archivos por extension");

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorExtension(mensaje.quien,mensaje.metadato);

	//Actualiza los metadatos del archivo
	}else if(mensaje.tipo == "PUTusuariosarchivosactualizar"){

		this->log->debug("Actualizando metadatos del archivo");

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.actualizarArchivo(mensaje.quien,cuerpo);

	}else if(mensaje.tipo == "PUTusuariosarchivosrestaurar"){

		this->log->debug("Restaurando archivo");

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.restaurarArchivo(mensaje.quien,cuerpo);

	//Retorna los archivos que el usuario posee en la papelera
	}else if(mensaje.tipo == "GETusuariospapelera"){

		this->log->debug("Buscando archivos en la papelera");

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.obtenerArchivosPapelera(mensaje.quien);

	}else if(mensaje.tipo == "PUTusuariosarchivosrecuperar"){

		this->log->debug("Recuperando archivo de la papelera");

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.recuperarArchivo(mensaje.quien,cuerpo);

	}else{

		this->log->warn("URL incorrecta: "+mensaje.tipo);

		Respuesta error;
		error.agregarEstado("ERROR");
		error.agregarMensaje("URL incorrecta");
		respuesta=error.obtenerRespuesta();

	}

	return respuesta;

}

void AdministradorServidor::cerrar(){

	Respuesta respuesta;
	respuesta.agregarEstado("ERROR");
	respuesta.agregarMensaje("El archivo no existe");

	const string &error=respuesta.obtenerRespuesta();

	mg_printf(c, "HTTP/1.0 200 OK\r\nContent-Length: %d\r\n"
				"Content-Type: application/json\r\n\r\n%s",
				(int) error.size(), error.c_str());

}

