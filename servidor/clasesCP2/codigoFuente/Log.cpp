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

	//this->ArchivoError.open ("LogError.txt", std::ofstream::out | std::ofstream::app);

}

void Log::inicializarWarn(){

	this->Warn = true;

	//this->ArchivoWarn.open ("LogWarn.txt", std::ofstream::out | std::ofstream::app);

}

void Log::inicializarInfo(){

	this->Info = true;

	//this->ArchivoInfo.open ("LogInfo.txt", std::ofstream::out | std::ofstream::app);

}

void Log::inicializarDebug(){

	this->Debug = true;

	//this->ArchivoDebug.open ("LogDebug.txt", std::ofstream::out | std::ofstream::app);

}

void Log::inicializarTrace(){

	this->Trace = true;

	//this->ArchivoTrace.open ("LogTrace.txt", std::ofstream::out | std::ofstream::app);

}

void Log::error(const string &mensaje){

	if ( this->Error ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [ERROR]	" <<  mensaje << "\n";
		this->Archivo.flush();
		this->mtx.unlock();

	}

}

void Log::warn(const string &mensaje){

	if ( this->Warn ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [WARN]	" <<  mensaje << "\n";
		this->Archivo.flush();
		this->mtx.unlock();

	}

}

void Log::info(const string &mensaje){

	if ( this->Info ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [INFO]	" <<  mensaje << "\n";
		this->Archivo.flush();
		this->mtx.unlock();

	}

}

void Log::debug(const string &mensaje){

	if ( this->Debug ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [DEBUG]	" <<  mensaje << "\n";
		this->Archivo.flush();
		this->mtx.unlock();

	}

}

void Log::trace(const string &mensaje){

	if ( this->Trace ){

		this->mtx.lock();
		this->Archivo << fecha.obtenerFecha() << " [TRACE]	" <<  mensaje << "\n";
		this->Archivo.flush();
		this->mtx.unlock();

	}

}

Log::Log() {

	this->Debug = false;
	this->Error = false;
	this->Info = false;
	this->Trace = false;
	this->Warn = false;

	this->Archivo.open("Log.txt", std::ofstream::out | std::ofstream::app);

}

Log::~Log() {

	if ( this->Debug || this->Error || this->Info || this->Trace )

		this->Archivo.close();

	/*if ( this->Debug )
		this->ArchivoDebug.close();
	if ( this->Error )
		this->ArchivoError.close();
	if ( this->Info )
		this->ArchivoInfo.close();
	if ( this->Warn )
		this->ArchivoWarn.close();
	if ( this->Trace )
		this->ArchivoTrace.close();
*/
}

void Log::destruirInstanciaLog(){

	if(instanciaLog != NULL)
		delete instanciaLog;

}
