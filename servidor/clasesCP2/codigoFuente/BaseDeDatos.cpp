#include "../cabeceras/BaseDeDatos.h"

BasedeDatos* BasedeDatos::unicaInstancia = NULL;
mutex BasedeDatos::mtx2;

BasedeDatos * BasedeDatos::obteberInstancia(){

	if( unicaInstancia == NULL ){
		mtx2.lock();
		if( unicaInstancia == NULL ){
			unicaInstancia = new BasedeDatos();
			atexit(&destruirInstancia);
		}
		mtx2.unlock();
	}
	return unicaInstancia;

}

bool BasedeDatos::guardar(const int TIPO,const string &clave,const string &valor){

	this->mtx.lock();

	this->log->debug("Se guardan datos en la base de datos");
	this->log->trace("Se guardan datos: "+valor+" del con clave: "+clave+" en la base de datos");

	WriteBatch batch;
	batch.Put(handles[TIPO], Slice(clave), Slice(valor));

	estado = db->Write(WriteOptions(), &batch);
	this->mtx.unlock();

	return estado.ok();

}

const string BasedeDatos::leer(const int TIPO,const string &clave){

	string datosExistente;
	
	this->log->debug("Se leen datos en la base de datos");
	this->log->trace("Se leen datos: "+clave+" de la base de datos");

	estado = db->Get(ReadOptions(), handles[TIPO], Slice(clave), &datosExistente);

	return datosExistente;

}

bool BasedeDatos::eliminar(const int TIPO,const string &clave){

	this->mtx.lock();

	this->log->debug("Se eliminan datos en la base de datos");
	this->log->trace("Se eliminan datos: "+clave+" de la base de datos");

	WriteBatch batch;
	batch.Delete(handles[TIPO], Slice(clave));
	estado = db->Write(WriteOptions(), &batch);

	this->mtx.unlock();

}

BasedeDatos::~BasedeDatos() {

	this->log->debug("Se cierra la base de datos");

	for (auto handle : handles) {
		delete handle;
	}
	delete db;

}

//METODOS PRIVADOS

BasedeDatos::BasedeDatos() {

	this->log = Log::obteberInstanciaLog();

	dirPath = "./testdb/";

	this->log->info("Abriendo base de datos en "+dirPath);

	Options opciones;
	opciones.create_if_missing = true;
	opciones.error_if_exists = true;
	estado = DB::Open(opciones,dirPath, &db);

	if(estado.ok()){

		this->log->debug("Creando la base de datos");
		this->inicializarColumnas();

	}

	this->log->debug("La base de datos ya existe, cargando datos");
	this->cargarColumnas();



}
void BasedeDatos::destruirInstancia(){
	if(unicaInstancia != NULL)
		delete unicaInstancia;
}

void BasedeDatos::inicializarColumnas(){

	ColumnFamilyHandle* usuarios;
	ColumnFamilyHandle* archivos;
	ColumnFamilyHandle* etiquetas;
	ColumnFamilyHandle* nombre;
	ColumnFamilyHandle* extension;
	ColumnFamilyHandle* propietario;

	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"USUARIOS", &usuarios);
	if( !estado.ok() ){

		this->log->error("La base de datos no se pudo cargar");
		exit(-1);

	}
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ARCHIVOS", &archivos);
	if( !estado.ok() ){

		this->log->error("La base de datos no se pudo cargar");
		exit(-1);

	}
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"ETIQUETAS", &etiquetas);
	if( !estado.ok() ){

		this->log->error("La base de datos no se pudo cargar");
		exit(-1);

	}
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"NOMBRE", &nombre);
	if( !estado.ok() ){

		this->log->error("La base de datos no se pudo cargar");
		exit(-1);

	}
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"EXTENSION", &extension);
	if( !estado.ok() ){

		this->log->error("La base de datos no se pudo cargar");
		exit(-1);

	}
	estado = db->CreateColumnFamily(ColumnFamilyOptions(),"PROPIETARIO", &propietario);
	if( !estado.ok() ){

		this->log->error("La base de datos no se pudo cargar");
		exit(-1);

	}
	delete usuarios;
	delete archivos;
	delete etiquetas;
	delete nombre;
	delete extension;
	delete propietario;

	delete db;

}

void BasedeDatos::cargarColumnas(){

	vector<ColumnFamilyDescriptor> column_families;

	column_families.push_back(ColumnFamilyDescriptor(kDefaultColumnFamilyName, ColumnFamilyOptions()));

	column_families.push_back(ColumnFamilyDescriptor("USUARIOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("ARCHIVOS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("ETIQUETAS", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("NOMBRE", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("EXTENSION", ColumnFamilyOptions()));
	column_families.push_back(ColumnFamilyDescriptor("PROPIETARIO", ColumnFamilyOptions()));

	estado = DB::Open(DBOptions(), dirPath, column_families, &handles, &db);

	if( !estado.ok() ){

		this->log->error("La base de datos no se pudo cargar");
		exit(-1);

	}

}
