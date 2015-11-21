#include "../cabeceras/Log.h"

Log* Log::instanciaLog = NULL;

Log * Log::obteberInstanciaLog(){

	if( instanciaLog == NULL ){

		instanciaLog = new Log();
		atexit(&destruirInstanciaLog);

	}

	return instanciaLog;

}

void Log::inicializarError(){

	this->Error = true;

}

void Log::inicializarWarn(){

	this->Warn = true;

}

void Log::inicializarInfo(){

	this->Info = true;
}

void Log::inicializarDebug(){

	this->Debug = true;

}

void Log::inicializarTrace(){

	this->Trace = true;

}

void Log::error(const string &mensaje){

	if ( this->Error ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [ERROR]	" <<  mensaje << "\n";
		this->mtx.unlock();

	}

}

void Log::warn(const string &mensaje){

	if ( this->Warn ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [WARN]	" <<  mensaje << "\n";
		this->mtx.unlock();

	}

}

void Log::info(const string &mensaje){

	if ( this->Info ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [INFO]	" <<  mensaje << "\n";
		this->mtx.unlock();

	}

}

void Log::debug(const string &mensaje){

	if ( this->Debug ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [DEBUG]	" <<  mensaje << "\n";
		this->mtx.unlock();

	}

}

void Log::trace(const string &mensaje){

	if ( this->Trace ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [TRACE]	" <<  mensaje << "\n";
		this->mtx.unlock();

	}

}

Log::Log() {

	this->Debug = false;
	this->Error = false;
	this->Info = false;
	this->Trace = false;
	this->Warn = false;

	this->Archivo.open("Log.txt", ofstream::out  | ofstream::binary );

}

Log::~Log() {

	if ( this->Debug || this->Error || this->Info || this->Trace )

		this->Archivo.close();

}

void Log::destruirInstanciaLog(){

	if(instanciaLog != NULL)
		delete instanciaLog;

}
