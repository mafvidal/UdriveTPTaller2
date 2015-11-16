
#include <iostream>
#include "BaseDeDatos.h"
#include "json/json.h"
#include "Actualizador.h"
#include "Usuario.h"
#include "Archivo.h"
#include "Hash.h"
#include "Buscador.h"
#include "Restaurador.h"
#include "mongoose.h"
#include "Servidor.h"
#include <pthread.h>
#include "Directorio.h"
#include "Log.h"

using namespace std;


void *arrancarServidor(void *threadid)
{

	((Servidor*)threadid)->arrancar();

}

int main(int argc, char *argv[]) {

	Log * log = Log::obteberInstanciaLog();

	for (int i=0;i<argc;i++){

		if ( *argv[i] == 'e' )
			log->inicializarError();

		if ( *argv[i] == 'd' )
			log->inicializarDebug();

		if ( *argv[i] == 'i' )
			log->inicializarInfo();

		if ( *argv[i] == 't' )
			log->inicializarTrace();

		if ( *argv[i] == 'w' )
			log->inicializarWarn();

	}

	BasedeDatos *baseDeDatos = BasedeDatos::obteberInstancia();

	log->info("Inicia servidor");

	//Creo el directorio inicial
	Directorio directorio;
	directorio.crearDirectorioPrincipal("./Udrive/");

	bool tengoQueSalir=false;
	char salir='a';
	pthread_t threads;
	Servidor ser;

	int resultado = pthread_create(&threads, NULL,arrancarServidor, &ser);
 	if (resultado){
		log->error( "No se pudo crear el hilo para el servidor" );
 		log->info( "Finaliza el servidor" );
		exit(-1);
     	}

	while(!tengoQueSalir){

		cout<<"Ingrese q y presione enter para salir"<<endl;
		cin>>salir;
		tengoQueSalir = salir == 'q';

	}

	ser.detener();

	pthread_join(threads,NULL);

	log->info( "Finaliza el servidor" );

	return 0;

}
