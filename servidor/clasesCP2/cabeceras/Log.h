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
	void error(const string &mensaje);
	void warn(const string &mensaje);
	void info(const string &mensaje);
	void debug(const string &mensaje);
	void trace(const string &mensaje);
	virtual ~Log();
private:
	Log();
	static void destruirInstanciaLog();
};

#endif /* LOG_H_ */
