
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

using namespace std;


void *arrancarServidor(void *threadid)
{

	((Servidor*)threadid)->arrancar();
	//ser.arrancar();

}

int main() {

	BasedeDatos *baseDeDatos = BasedeDatos::obteberInstancia();

	//Creo el directorio inicial
	Directorio directorio;
	directorio.crearDirectorioPrincipal("./Udrive/");

	bool tengoQueSalir=false;
	char salir='a';
	pthread_t threads;
	Servidor ser;

	int resultado = pthread_create(&threads, NULL,arrancarServidor, &ser);
 	if (resultado){
		cout << "Error:unable to create thread," << resultado << endl;
		exit(-1);
     	}

	while(!tengoQueSalir){

		cout<<"Ingrese q y presione enter para salir"<<endl;
		cin>>salir;
		tengoQueSalir = salir == 'q';

	}

	ser.detener();

	pthread_join(threads,NULL);

	//pthread_exit(NULL);

	return 0;
}
