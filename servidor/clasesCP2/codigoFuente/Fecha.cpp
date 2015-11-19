#include "../cabeceras/Fecha.h"


string Fecha::obtenerFecha(){

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%D %r",timeinfo);

	return buffer;

}
