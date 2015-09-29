#include "BaseDeDatos.h"

BaseDeDatos::BaseDeDatos(string directorio) {

	dirPath = directorio;
	Options opciones;
	opciones.create_if_missing = true;
	opciones.error_if_exists = true;
	estado = DB::Open(opciones,dirPath, &db);
	if(estado.ok())
		this->inicializarColumnas();
	
	this->cargarColumnas();

}


bool BaseDeDatos::agregarUsuario(string nombreUsuario,string clave,string metadatosJson,float cuota){

	DatosDeUsuario dato;

	string datosUsuarios;

	datosUsuarios = dato.obtenerDatosDeUsuarios(metadatosJson,clave,cuota);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datosUsuarios));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::existeUsuario(string nombreUsuario){

	string value;
	estado = db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &value);
	return estado.ok();

}


bool BaseDeDatos::esLaClaveCorrecta(string nombreUsuario,string clave){

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	return (clave == datos.clave(datosUsuario));

}

string BaseDeDatos::getMetaDatosUsuario(string nombreUsuario){

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	return datos.obtenerMetadatosDelUsuario(datosUsuario);

}

bool BaseDeDatos::setDatosUsuario(string nombreUsuario, string metaDatosUsuario){

	string datoUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datoUsuario);

	DatosDeUsuario datos;

	datoUsuario = datos.modificarDatosDeUsuarios(datoUsuario,metaDatosUsuario);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datoUsuario));
	estado = db->Write(WriteOptions(), &batch);

	return estado.ok();

}

bool BaseDeDatos::agregarArchivo(string nombreUsuario,string metadatos,float espacio){

	//Guardo archivo
	DatosDeArchivos datosArchivo;
	string datosArchivoAGuardar;

	datosArchivoAGuardar = datosArchivo.obtenerDatos(metadatos);
	
	unsigned int hash = this->obtenerHash(datosArchivo.getNombreCompleto(datosArchivoAGuardar));
	string hashString = this->convertirAString(hash);

	string archivoExistente;

	estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);
	while(estado.ok()){
		hash++;
		hashString = this->convertirAString(hash);
		estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);
	}

	this->cargarEtiquetas(datosArchivo.listaDeEtiquetas(metadatos),nombreUsuario,hashString);
	//this->cargarEtiquetas(datosArchivo.listaDeEtiquetas(metadatos),datosArchivo.propietario(metadatos),hashString);
	this->cargarMetadatos(datosArchivo.propietario(metadatos),nombreUsuario,hashString,PROPIETARIO);
	this->cargarMetadatos(datosArchivo.nombre(metadatos),nombreUsuario,hashString,NOMBRE);
	this->cargarMetadatos(datosArchivo.extension(metadatos),nombreUsuario,hashString,EXTENSION);

	WriteBatch batchArchivos;
	batchArchivos.Put(handles[ARCHIVOS], Slice(hashString), Slice(datosArchivoAGuardar));
	estado = db->Write(WriteOptions(), &batchArchivos);

	//Guardo el archivo en el usuario

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	WriteBatch batch;

	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datos.agregarArchivoNuevo(datosUsuario,hashString,espacio)));
	estado = db->Write(WriteOptions(), &batch);

}

list<string> BaseDeDatos::getArchivos(string nombreUsuario){

	return this->obtenerArchivos(nombreUsuario,"NoPapelera");

}

void BaseDeDatos::eliminarLogicamenteArchivo(string nombreUsuario,string metadatosArchivo,float espacio){

	//eliminar archivo
	DatosDeArchivos datosArchivo;
	string nombreCompleto;

	nombreCompleto = datosArchivo.getNombreCompleto(datosArchivo.obtenerDatos(metadatosArchivo));
	
	unsigned int hash = this->obtenerHash(nombreCompleto);
	string hashString = this->convertirAString(hash);

	string archivoExistente;
	string nombreExistente;

	estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);

	nombreExistente = datosArchivo.getNombreCompleto(archivoExistente);

	while(nombreExistente != nombreCompleto){
		hash++;
		hashString = this->convertirAString(hash);
		estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);
		nombreExistente = datosArchivo.getNombreCompleto(archivoExistente);
	}

	string nuevohash = "~"+hashString;

	WriteBatch batchArchivos;
	batchArchivos.Put(handles[ARCHIVOS], Slice(nuevohash), Slice(datosArchivo.obtenerDatos(metadatosArchivo)));
	batchArchivos.Delete(handles[ARCHIVOS], Slice(hashString));
	estado = db->Write(WriteOptions(), &batchArchivos);

	//Eliminar archivo del usuario
	
	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	datosUsuario = datos.eliminarArchivo(datosUsuario,hashString,espacio);
	datosUsuario = datos.agregarArchivoNuevo(datosUsuario,nuevohash,0);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datosUsuario));
	estado = db->Write(WriteOptions(), &batch);

}

void BaseDeDatos::eliminarFisicamenteArchivo(string nombreUsuario,string metadatosArchivo){

	//eliminar archivo
	DatosDeArchivos datosArchivo;
	string nombreCompleto;

	nombreCompleto = datosArchivo.getNombreCompleto(datosArchivo.obtenerDatos(metadatosArchivo));
	
	unsigned int hash = this->obtenerHash(nombreCompleto);
	string hashString = "~"+this->convertirAString(hash);

	string archivoExistente;
	string nombreExistente;

	estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);

	nombreExistente = datosArchivo.getNombreCompleto(archivoExistente);

	while(nombreExistente != nombreCompleto){
		hash++;
		hashString = "~"+this->convertirAString(hash);
		estado = db->Get(ReadOptions(), handles[ARCHIVOS], Slice(hashString), &archivoExistente);
		nombreExistente = datosArchivo.getNombreCompleto(archivoExistente);
	}

	WriteBatch batchArchivos;
	batchArchivos.Delete(handles[ARCHIVOS], Slice(hashString));
	estado = db->Write(WriteOptions(), &batchArchivos);

	//Eliminar archivo del usuario

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	datosUsuario = datos.eliminarArchivo(datosUsuario,hashString,0);

	WriteBatch batch;
	batch.Put(handles[USARIOS], Slice(nombreUsuario), Slice(datosUsuario));
	estado = db->Write(WriteOptions(), &batch);

}

list<string> BaseDeDatos::getArchivosEnPapelera(string nombreUsuario){

	return this->obtenerArchivos(nombreUsuario,"Papelera");

}

list<string> BaseDeDatos::buscarPorEtiquetas(string nombreUsuario,string etiqueta){

	return buscarPorMetadato(nombreUsuario,etiqueta,ETIQUETAS);

	list<string> archivosLista;
	list<string> hasharchivosLista;
	string datosEtiquetas;
	MetadatosConsulta datos;

	string nombre=nombreUsuario+etiqueta;
	
	estado = db->Get(ReadOptions(), handles[ETIQUETAS], Slice(nombre), &datosEtiquetas);

	if(!estado.ok())
		return archivosLista;

	hasharchivosLista = datos.archivos(datosEtiquetas);

	for(list<string>::iterator it = hasharchivosLista.begin(); it != hasharchivosLista.end(); it++){
		
		DatosDeArchivos datosArchivo;
		string datosDelArchivo;

		db->Get(ReadOptions(), handles[ARCHIVOS], Slice((*it)), &datosDelArchivo);

		archivosLista.push_back(datosArchivo.obtenerMetadatos(datosDelArchivo));
	}

	return archivosLista;

}

list<string> BaseDeDatos::buscarPorExtension(string nombreUsuario,string extension){

	return buscarPorMetadato(nombreUsuario,extension,EXTENSION);

}

list<string> BaseDeDatos::buscarPorNombre(string nombreUsuario,string nombre){

	return buscarPorMetadato(nombreUsuario,nombre,NOMBRE);

}

list<string> BaseDeDatos::buscarPorPropietario(string nombreUsuario,string propietario){

	return buscarPorMetadato(nombreUsuario,propietario,PROPIETARIO);

}


BaseDeDatos::~BaseDeDatos() {

	for (auto handle : handles) {
		delete handle;
	}
	delete db;

}

unsigned int BaseDeDatos::obtenerHash(string archivo){

	unsigned int hash = 0;

	for(int i=0; i<archivo.size(); ++i)
	{
		hash += archivo[i];
		hash += (hash << 10);
 		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;

}

string BaseDeDatos::convertirAString(unsigned int hash){

	string hashString;
	ostringstream convertir;
	convertir << hash;
	hashString = convertir.str();

	return hashString;

}
void BaseDeDatos::inicializarColumnas(){

	ColumnFamilyHandle* usuarios;
	ColumnFamilyHandle* archivos;
	ColumnFamilyHandle* etiquetas;
	ColumnFamilyHandle* nombre;
	ColumnFamilyHandle* extension;
	ColumnFamilyHandle* propietario;

	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"USUARIOS", &usuarios);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ARCHIVOS", &archivos);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ETIQUETAS", &etiquetas);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"NOMBRE", &nombre);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"EXTENSION", &extension);
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"PROPIETARIO", &propietario);

	delete usuarios;
	delete archivos;
	delete etiquetas;
	delete nombre;
	delete extension;
	delete propietario;

	delete db;

}

void BaseDeDatos::cargarColumnas(){

	vector<ColumnFamilyDescriptor> column_families;

	column_families.push_back(ColumnFamilyDescriptor(
			kDefaultColumnFamilyName, ColumnFamilyOptions()));

	column_families.push_back(ColumnFamilyDescriptor("USUARIOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("ARCHIVOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("ETIQUETAS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("NOMBRE", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("EXTENSION", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("PROPIETARIO", ColumnFamilyOptions()));

	estado = DB::Open(DBOptions(), dirPath, column_families, &handles, &db);

}
list<string> BaseDeDatos::obtenerArchivos(string nombreUsuario,string modo){

	list<string> listaDeArchivos;
	list<string> listaDeMetadatos;

	string datosUsuario;

	db->Get(ReadOptions(), handles[USARIOS], Slice(nombreUsuario), &datosUsuario);

	DatosDeUsuario datos;

	listaDeArchivos = datos.obtenerArchivos(datosUsuario);

	for(list<string>::iterator it = listaDeArchivos.begin(); it != listaDeArchivos.end(); it++){
		if( modo == "Papelera" ){
			if((*it)[0] == '~'){
				DatosDeArchivos datosArchivo;
				string datosDelArchivo;

				db->Get(ReadOptions(), handles[ARCHIVOS], Slice((*it)), &datosDelArchivo);

				listaDeMetadatos.push_back(datosArchivo.obtenerMetadatos(datosDelArchivo));
			}
		}else{
			if((*it)[0] != '~'){
				DatosDeArchivos datosArchivo;
				string datosDelArchivo;

				db->Get(ReadOptions(), handles[ARCHIVOS], Slice((*it)), &datosDelArchivo);

				listaDeMetadatos.push_back(datosArchivo.obtenerMetadatos(datosDelArchivo));
			}
		}

	}

	return listaDeMetadatos;

}
void BaseDeDatos::cargarEtiquetas(list<string> etiquetas, string nombreUsuario,string hashArchivo){
	
	MetadatosConsulta datos;

	for(list<string>::iterator it = etiquetas.begin(); it != etiquetas.end(); it++){

		string nombre=nombreUsuario+(*it);
		string archivos;
	
		estado = db->Get(ReadOptions(), handles[ETIQUETAS], Slice(nombre), &archivos);
		
		if(!estado.ok()){

			archivos = datos.contruir(hashArchivo);

		}else{

			archivos = datos.cargarArchivo(archivos,hashArchivo);

		}
		WriteBatch batch;
		batch.Put(handles[ETIQUETAS], Slice(nombre), Slice(archivos));
		estado = db->Write(WriteOptions(), &batch);

	}


}
void BaseDeDatos::cargarMetadatos(string metadato, string nombreUsuario,string hashArchivo,const int TIPO){

	MetadatosConsulta datos;

	string nombre=nombreUsuario+metadato;
	string archivos;
	
	estado = db->Get(ReadOptions(), handles[TIPO], Slice(nombre), &archivos);
		
	if(!estado.ok()){

		archivos = datos.contruir(hashArchivo);

	}else{

		archivos = datos.cargarArchivo(archivos,hashArchivo);

	}

	WriteBatch batch;
	batch.Put(handles[TIPO], Slice(nombre), Slice(archivos));
	estado = db->Write(WriteOptions(), &batch);

}
list<string> BaseDeDatos::buscarPorMetadato(string nombreUsuario,string metadato,const int TIPO){

	list<string> archivosLista;
	list<string> hashArchivosLista;
	string datosExistente;
	MetadatosConsulta datos;

	string nombre=nombreUsuario+metadato;
	
	estado = db->Get(ReadOptions(), handles[TIPO], Slice(nombre), &datosExistente);

	if(!estado.ok())
		return archivosLista;

	hashArchivosLista = datos.archivos(datosExistente);

	for(list<string>::iterator it = hashArchivosLista.begin(); it != hashArchivosLista.end(); it++){
		
		DatosDeArchivos datosArchivo;
		string datosDelArchivo;

		db->Get(ReadOptions(), handles[ARCHIVOS], Slice((*it)), &datosDelArchivo);

		archivosLista.push_back(datosArchivo.obtenerMetadatos(datosDelArchivo));
	}

	return archivosLista;

}
