
#include "BaseDeDatos.h"
#include <iostream>


using namespace std;

int main(int argc, char** argv) {

	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","ROCKSDB");
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

