
#include "DatosDeUsuario.h"

DatosDeUsuario::DatosDeUsuario(string clave,float cuota) {

	this->clave = clave;
	this->cuota = cuota;
	this->cuotaUsada = 0;

	this->email = "";
	this->nombre = "";
	this->ubicacionFoto = "";
	this->ultimaUbicacion = "";

}
DatosDeUsuario::DatosDeUsuario(string datos) {

	this->cargarDatos(datos);

}
void DatosDeUsuario::cargarDatos(string datos){

	Value root;
	Reader reader;

	reader.parse(datos, root,false);

	this->clave = root.get("Clave", "" ).asString();//.asString();
	this->cuotaUsada = root.get("CuotaUsada", "" ).asFloat();
	this->cuota = root.get("Cuota", "" ).asFloat();

	Value files = root["Archivos"];
	for ( int indice = 0; indice < files.size(); ++indice )  // Iterates over the sequence elements.
		this->archivos.push_back(files[indice].asString());

	this->nombre = root["MetaDatos"].get("Nombre","").asString();
	this->email = root["MetaDatos"].get("Email","").asString();
	this->ubicacionFoto = root["MetaDatos"].get("Foto","").asString();
	this->ultimaUbicacion = root["MetaDatos"].get("UltimaUbicacion","").asString();//asString().size();
	//cout<<root["MetaDatos"].get("UltimaUbicacion","").asString().size()<<endl;

}

void DatosDeUsuario::cargarDatosDelUsuario(string datosDeUsuario){

	Value root;
	Reader reader;

	reader.parse(datosDeUsuario, root,false);

	this->nombre = root.get("Nombre", "" ).asString();
	this->email = root.get("Email", "" ).asString();
	this->ubicacionFoto = root.get("Foto", "" ).asString();
	this->ultimaUbicacion = root.get("UltimaUbicacion", "" ).asString();

}

string DatosDeUsuario::getDatos(){

	Value datos;
	Value metadatos;
	Value archivos(arrayValue);
	for (list<string>::iterator it = this->archivos.begin(); it != this->archivos.end(); it++)
		archivos.append(Value((*it)));
	datos["Archivos"] = archivos;
	metadatos["Nombre"] = this->nombre;
	metadatos["Email"] = this->email;
	metadatos["UltimaUbicacion"] = this->ultimaUbicacion;
	metadatos["Foto"] = this->ubicacionFoto;
	datos["MetaDatos"] = metadatos;
	datos["Clave"] = this->clave;
	datos["Cuota"] = this->cuota;
	datos["CuotaUsada"] = this->cuotaUsada;

	return datos.toStyledString();

}

string DatosDeUsuario::getDatosDelUsuario(){

	Value metadatos;
	metadatos["Nombre"] = this->nombre;
	metadatos["Email"] = this->email;
	metadatos["UltimaUbicacion"] = this->ultimaUbicacion;
	metadatos["Foto"] = this->ubicacionFoto;

	return metadatos.toStyledString();

}

void DatosDeUsuario::setArchivo(string archivo, float espacio){

	this->archivos.push_back(archivo);
	this->cuotaUsada = this->cuotaUsada + espacio;

}

list<string> DatosDeUsuario::getArchivos(){

	return this->archivos;

}

void DatosDeUsuario::setCuota(float cuota){

	this->cuota = cuota;

}
void DatosDeUsuario::setClave(string clave){

	this->clave = clave;

}
string DatosDeUsuario::getClave(){

	return this->clave;

}
DatosDeUsuario::~DatosDeUsuario() {
}

