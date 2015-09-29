#include "DatosDeUsuario.h"

DatosDeUsuario::DatosDeUsuario() {

}
string DatosDeUsuario::obtenerDatosDeUsuarios(string metadatosJson,string clave,float cuota){

	Value metadatos;
	Value datos;
	Reader reader;
	Value archivos(arrayValue);
	Value archivosCompartidos(arrayValue);

	reader.parse(metadatosJson, metadatos,false);

	datos["Clave"] = clave;
	datos["Cuota"] = cuota;
	datos["CuotaUsada"] = 0;
	datos["Archivos"] = archivos;
	datos["ArchivosCompartidos"] = archivosCompartidos;
	datos["MetaDatos"] = metadatos;

	return datos.toStyledString();

}
string DatosDeUsuario::modificarDatosDeUsuarios(string datosJson,string metaDatosJson){

	Value datos;
	Value metadatos;
	Reader reader;

	reader.parse(datosJson, datos,false);
	reader.parse(metaDatosJson, metadatos,false);

	datos["MetaDatos"] = metadatos;

	return datos.toStyledString();

}
string DatosDeUsuario::obtenerMetadatosDelUsuario(string datosJson){

	Value metadatos;
	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	metadatos = datos["MetaDatos"];

	return metadatos.toStyledString();

}
string DatosDeUsuario::modificarClave(string datosJson,string clave){

	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	datos["Clave"] = clave;

	return datos.toStyledString();

}
string DatosDeUsuario::clave(string datosJson){

	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	return datos.get("Clave","").asString();

}
string DatosDeUsuario::agregarArchivoNuevo(string datosJson,string hashArchivo,float espacio){

	Value datos;
	Reader reader;
	float espacioNuevo;

	reader.parse(datosJson, datos,false);

	datos["Archivos"].append(Value(hashArchivo));

	espacioNuevo = datos.get("CuotaUsada",0).asFloat() + espacio;

	datos["CuotaUsada"] = espacioNuevo;

	return datos.toStyledString();


}
string DatosDeUsuario::eliminarArchivo(string datosJson,string hashArchivo,float espacio){

	return this->eliminar(datosJson,hashArchivo,"Archivos",espacio);

}
string DatosDeUsuario::eliminarArchivoCompartido(string datosJson,string hashArchivo,float espacio){

	return this->eliminar(datosJson,hashArchivo,"ArchivosCompartidos",espacio);

}
float DatosDeUsuario::cuota(string datosJson){

	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	return datos.get("Cuota",0).asFloat();

}
float DatosDeUsuario::cuotaUsada(string datosJson){

	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	return datos.get("CuotaUsada",0).asFloat();

}
string DatosDeUsuario::modificarCuota(string datosJson,float cuotaNueva){

	Value datos;
	Reader reader;

	reader.parse(datosJson, datos,false);

	datos["Cuota"] = cuotaNueva;

	return datos.toStyledString();

}
list<string> DatosDeUsuario::obtenerArchivos(string datosJson){

	Value datos;
	Reader reader;
	list<string> archivos;

	reader.parse(datosJson, datos,false);


	Value archivosJson = datos["Archivos"];
	for ( int indice = 0; indice < archivosJson.size(); ++indice )
		archivos.push_back(archivosJson[indice].asString());

	return archivos;

}
DatosDeUsuario::~DatosDeUsuario() {
}
string DatosDeUsuario::eliminar(string datosJson,string hashArchivo,string tipo,float espacio){

	Value datos;
	Reader reader;
	Value archivosNuevos(arrayValue);
	Value archivos(arrayValue);
	float espacioNuevo;

	reader.parse(datosJson, datos,false);

	archivos = datos[tipo];

	for ( int indice = 0; indice < archivos.size(); ++indice ){
		if(archivos[indice].asString() != hashArchivo ){
			archivosNuevos.append(Value(archivos[indice].asString()));
		}
	}

	espacioNuevo = datos.get("CuotaUsada",0).asFloat() - espacio;

	datos["CuotaUsada"] = espacioNuevo;

	datos[tipo] = archivosNuevos;

	return datos.toStyledString();

}
