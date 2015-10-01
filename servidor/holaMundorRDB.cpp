/*
#include "BaseDeDatos.h"
#include <iostream>
#include <mongoose.h>
#include <json/json.h>
#include <fstream>




using namespace std;

int main(int argc, char** argv) {

	
	/*struct mg_server *server = mg_create_server(NULL, NULL);
	mg_set_option(server, "document_root", ".");	  // Serve current directory
	mg_set_option(server, "listening_port", "8080");  // Open port 8080

	for (int i=0;i<3;i++) {
		cout<<i<<endl;
		mg_poll_server(server, 1000);   // Infinite loop, Ctrl-C to stop
	}

	mg_destroy_server(&server);*/

	/*BaseDeDatos base("testdb/");
	base.setUsuario("Juan","ROCKSDB",800);
	if (base.existeUsuario("Juan"))
		cout<<"Existe"<<endl;
	else
		cout<<"No Existe"<<endl;
	if (base.existeUsuario("Pedro"))
		cout<<"Existe"<<endl;
	else
		cout<<"No Existe"<<endl;

	if (base.esLaClaveCorrecta("Juan","ROCKSDB"))
		cout<<"SI"<<endl;
	else
		cout<<"NO"<<endl;
	if (base.esLaClaveCorrecta("Juan","ROC"))
		cout<<"SI"<<endl;
	else
		cout<<"NO"<<endl;

	return 0;

}
*/
//============================================================================
// Name        : ServidorMongooseCPP.cpp
// Author      : Facundo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "Server.h"
#include "WebController.h"
#include "MyController.h"
#include "FilesController.h"
#include "BaseDeDatos.h"

using namespace std;
using namespace Mongoose;

int main()
{
    MyController myController;
    FilesController filesController;

    Server server(8080);
    server.registerController(&myController);
    server.registerController(&filesController);

    server.start();

    while (1) {
        sleep(10);
    }
}
