/*
 * Log.h
 *
 *  Created on: 13 de nov. de 2015
 *      Author: mafv
 */

#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <fstream>
#include <mutex>
#include "Fecha.h"

using namespace std;

/**
* Clase encargada de generar el log del sistema
*/
class Log {
private:
	mutex mtx;
	Fecha fecha;
	bool Error;
	bool Warn;
	bool Info;
	bool Debug;
	bool Trace;
	ofstream ArchivoError;
	ofstream ArchivoWarn;
	ofstream ArchivoInfo;
	ofstream ArchivoDebug;
	ofstream ArchivoTrace;
	ofstream Archivo;
	static Log * instanciaLog;
public:
	static Log * obteberInstanciaLog();
	void inicializarError();
	void inicializarWarn();
	void inicializarInfo();
	void inicializarDebug();
	void inicializarTrace();
	/**
	* Almacena los mensajes de error
	*/
	void error(const string &mensaje);
	/**
	* Almacena los mensajes de warning
	*/
	void warn(const string &mensaje);
	/**
	* Almacena los mensajes de informacion
	*/
	void info(const string &mensaje);
	/**
	* Almacena los mensajes de debug
	*/
	void debug(const string &mensaje);
	/**
	* Almacena los mensajes de trace
	*/
	void trace(const string &mensaje);
	virtual ~Log();
private:
	Log();
	static void destruirInstanciaLog();
};

#endif /* LOG_H_ */
