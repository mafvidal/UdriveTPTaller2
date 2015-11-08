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

					/*c->proto_handler = NULL;

					datos = new datosArchivo;

					ManejadorArchivosFisicos maf;

					datos->hashArchivo = maf.obtenerNombreDelArchivo(mensaje.hashArchivo);

					datos->bytes_left = hm.body.len;

					FILE *archivo;

					archivo = fopen (datos->hashArchivo.c_str(), "wb");

					this->archivos[datos->hashArchivo] = archivo;

					c->user_data = (void *) datos;

					mbuf_remove(&c->recv_mbuf, hm.body.p - c->recv_mbuf.buf);*/

					ManejadorArchivosFisicos maf(mensaje.hashArchivo);

					maf.crearArchivoFisico(c,hm);

					this->administrar();

				}else if( mensaje.tipo == "PUTusuariosarchivofisico" ){
					//cargar datos para actualizar archivo
				//Creo que esta no va aca
				}else if( mensaje.tipo == "GETusuariosarchivofisico" ) {
					//cargar datos para retornar archivo
				}
			}

		}else if ( this->ev == MG_EV_HTTP_REQUEST ){

			this->parsearMensaje();

			string respuesta = this->realizarOperacion();

			mg_printf(c, "HTTP/1.0 200 OK\r\nContent-Length: %d\r\n"
						"Content-Type: application/json\r\n\r\n%s",
						(int) respuesta.size(), respuesta.c_str());

		}

	}else if ( this->ev == MG_EV_RECV ){

		ManejadorArchivosFisicos maf;

		maf.cargarArchivo(c);

		/*size_t to_write = datos->bytes_left, written = 0;

		if (c->recv_mbuf.len < to_write)

			to_write = c->recv_mbuf.len;

		FILE * archivo = this->archivoss[datos->hashArchivo];

		written = fwrite(c->recv_mbuf.buf, 1, to_write, archivo);

		mbuf_remove(&c->recv_mbuf, written);
		datos->bytes_left -= written;
		if (datos->bytes_left <= 0) {

			mg_printf(c,
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: text/plain\r\n"
					"Connection: close\r\n\r\n"
					"Written %ld of POST data to a temp file\n\n",
					(long) ftell(this->archivoss[datos->hashArchivo]));

			fclose(this->archivoss[datos->hashArchivo]);
			delete datos;

			c->flags |= MG_F_SEND_AND_CLOSE;

		}*/

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
	mensaje.archivoFisico = tipo+archivos;
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
