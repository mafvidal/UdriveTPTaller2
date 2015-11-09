/*
 * AdministradorServidor.cpp
 *
 *  Created on: 3 de nov. de 2015
 *      Author: mafv
 */

#include "AdministradorServidor.h"
map<string,FILE*> AdministradorServidor::archivoss;


AdministradorServidor::AdministradorServidor(struct mg_connection *c, int ev, struct http_message p) {

	this->c = c;
	this->ev = ev;
	this->hm = p;

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

				if( mensaje.archivoFisico == "POSTusuariosarchivofisico" ){

					ManejadorArchivosFisicos maf(mensaje.hashArchivo);

					maf.crearArchivoFisico(c,hm);

					this->administrar();

				}else if( mensaje.archivoFisico == "PUTusuariosarchivofisico" ){

					ManejadorArchivosFisicos archivoFisico(mensaje.hashArchivo);

					archivoFisico.actualizarArchivoFisico(c,hm);

					this->administrar();

				}
			}

		}else if ( this->ev == MG_EV_HTTP_REQUEST ){

			this->parsearMensaje();

			if ( mensaje.archivoFisico == "GETusuariosarchivofisico" ){

				string respuesta="Falta...";

				mg_printf(c, "%s",respuesta.c_str());
				c->flags |= MG_F_SEND_AND_CLOSE;


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

	char buffer[100];
	snprintf(buffer, sizeof(buffer), "%.*s",(int) hm.uri.len, hm.uri.p);
	string texto=buffer;

	string tipo = "";
	string nombreUsuario = "";
	string archivos = "";
	string operacion = "";
	string metadato = "";
	string hashArchivo = "";

	istringstream iss(texto);
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
		}

	}

	mensaje.quien = nombreUsuario;
	mensaje.tipo = tipo+archivos+operacion;
	mensaje.metadato = metadato;
	mensaje.archivoFisico = tipo+archivos+metadato;
	mensaje.hashArchivo = hashArchivo;

}
string AdministradorServidor::determinarProtocolo(){

	if (this->sonIguales(&hm.method, &s_put_method)){

		return "PUT";

	}else if(this->sonIguales(&hm.method, &s_get_method)){

		return "GET";

	}else if(this->sonIguales(&hm.method, &s_post_method)){

		return "POST";

	}else if(this->sonIguales(&hm.method, &s_delele_method)){

		return "DELETE";

	}else{

		return "ERROR";

	}

}

string AdministradorServidor::realizarOperacion(){

	string respuesta;
	string cuerpo = hm.body.p;

	if(mensaje.tipo == "POSTusuarios"){

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.generar(mensaje.quien,cuerpo);

	}else if(mensaje.tipo == "POSTiniciarsesion"){

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.iniciarSesion(mensaje.quien,cuerpo);

	}else if(mensaje.tipo == "GETusuarios"){

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.obtenerDatos(mensaje.quien);

	}else if(mensaje.tipo == "PUTusuarios"){

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.actualizarDatos(mensaje.quien,cuerpo);

	}else if(mensaje.tipo == "GETusuariosarchivos"){

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.obtenerArchivos(mensaje.quien);

	}else if(mensaje.tipo == "DELETEusuariosarchivos"){

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.eliminarArchivo(mensaje.quien,cuerpo);

	}else if(mensaje.tipo == "POSTusuariosarchivos"){

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.crearArchivo(mensaje.quien,cuerpo);

	}else if(mensaje.tipo == "PUTusuariosarchivoscompartir"){

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.compartirArchivo(cuerpo);

	}else if(mensaje.tipo == "GETusuariosarchivosetiquetas"){

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorEtiquetas(mensaje.quien,mensaje.metadato);

	}else if(mensaje.tipo == "GETusuariosarchivosnombre"){

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorNombre(mensaje.quien,mensaje.metadato);

	}else if(mensaje.tipo == "GETusuariosarchivospropietario"){

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorPropietario(mensaje.quien,mensaje.metadato);

	}else if(mensaje.tipo == "GETusuariosarchivosextension"){

		ManejadorBuscador manejadorBuscador;
		respuesta = manejadorBuscador.buscarPorExtension(mensaje.quien,mensaje.metadato);

	}else if(mensaje.tipo == "PUTusuariosarchivosactualizar"){

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.actualizarArchivo(cuerpo);

	}else if(mensaje.tipo == "PUTusuariosarchivosrestaurar"){

		ManejadorArchivos manejadorArchivos;
		respuesta = manejadorArchivos.restaurarArchivo(cuerpo);

	}else if(mensaje.tipo == "GETusuariospapelera"){

		ManejadorUsuario manejadorUsuario;
		respuesta = manejadorUsuario.obtenerArchivosPapelera(mensaje.quien);

	}else{

		respuesta="ERROR";

	}

	return respuesta;

}
