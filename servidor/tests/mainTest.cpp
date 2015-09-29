#include <iostream>
#include <list>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BaseDeDatos.h"
#include "estructuras.h"
#include <fstream>
#include "json/json.h"

using namespace std;

string cargarJsonUsuario(){

	//Cargo el json de prueba
	Json::Value datosUsuario;
	Json::Reader reader;
	ifstream test("datosDeUsuario.json", ifstream::binary);
	reader.parse( test, datosUsuario, false );

	return datosUsuario.toStyledString();

}
string cargarJsonArchivo(string propietario){

	//Cargo el json de prueba
	Json::Value datosArchivo;
	Json::Reader reader;
	ifstream test("archivo.json", ifstream::binary);
	reader.parse( test, datosArchivo, false );
	datosArchivo["Propietario"]=propietario;
	
	return datosArchivo.toStyledString();

}

TEST(baseDeDatos, existeUsuario) {
	
	string datosUsuario = cargarJsonUsuario();

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Juan","Clave",datosUsuario,800);
	EXPECT_TRUE(base.existeUsuario("Juan"));

}

TEST(baseDeDatos, verificarInexistenciaDeUsuario){

	string datosUsuario = cargarJsonUsuario();

        BaseDeDatos base("testdb/");
        base.agregarUsuario("Juan","Clave",datosUsuario,800);
        EXPECT_FALSE(base.existeUsuario("Roberto"));

}

TEST(baseDeDatos, verificarClaveCorrecta) {

	string datosUsuario = cargarJsonUsuario();

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Juan","MiClave",datosUsuario,800);
	EXPECT_TRUE(base.esLaClaveCorrecta("Juan","MiClave"));

}

TEST(baseDeDatos, verificarClaveIncorrecta) {

	string datosUsuario = cargarJsonUsuario();

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Pedro","MiClave",datosUsuario,800);
	EXPECT_FALSE(base.esLaClaveCorrecta("Pedro","otraClave"));

}

TEST(baseDeDatos, almacenarDatosDeUnUsuarioExistenteYVerificarCorrectoAlmacenamiento){

	string datosUsuario = cargarJsonUsuario();

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Juan","MiClave",datosUsuario,800);
	string datos = base.getMetaDatosUsuario("Juan");

	Json::Value metadatos;
	Json::Reader reader;

	reader.parse(datos, metadatos);

	EXPECT_EQ("Juan",metadatos.get("Nombre", "" ).asString());
	EXPECT_EQ("juan@gmail.com",metadatos.get("Email", "" ).asString());
	EXPECT_EQ("juanFoto",metadatos.get("Foto", "" ).asString());
	EXPECT_EQ("La Pampa",metadatos.get("UltimaUbicacion", "" ).asString());

}

TEST(baseDeDatos, alAlmacenarUnArchivoEsteDebeEstarEnLaBase){

	string datosUsuario = cargarJsonUsuario();
	string datosArchivo = cargarJsonArchivo("Juan");

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Juan","MiClave",datosUsuario,800);
	
	base.agregarArchivo("Juan",datosArchivo,55);

	list<string> listaDeArchivos = base.getArchivos("Juan");

	Json::Value metadatos;
	Json::Reader reader;

	reader.parse(listaDeArchivos.front(), metadatos);

	EXPECT_EQ("colores",metadatos.get("Nombre", "" ).asString());

}

TEST(baseDeDatos, alEliminarUnArchivoYSolicitarArchivosDelUsuarioEsteNoDebeExistir){

	string datosUsuario = cargarJsonUsuario();
	string datosArchivo = cargarJsonArchivo("Pedro");

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Pedro","MiClave",datosUsuario,800);
	
	base.agregarArchivo("Pedro",datosArchivo,55);

	base.eliminarLogicamenteArchivo("Pedro",datosArchivo,55);

	list<string> listaDeArchivos = base.getArchivos("Pedro");

	EXPECT_EQ(listaDeArchivos.size(),0);

}

TEST(baseDeDatos, alEliminarUnArchivoEsteDebeEstarEnLaPapelera){

	string datosUsuario = cargarJsonUsuario();
	string datosArchivo = cargarJsonArchivo("Ramon");

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Ramon","MiClave",datosUsuario,800);
	
	base.agregarArchivo("Ramon",datosArchivo,55);
	base.eliminarLogicamenteArchivo("Ramon",datosArchivo,55);

	list<string> listaDeArchivos = base.getArchivosEnPapelera("Ramon");

	Json::Value metadatos;
	Json::Reader reader;

	reader.parse(listaDeArchivos.front(), metadatos);

	EXPECT_EQ("colores",metadatos.get("Nombre", "" ).asString());
	EXPECT_EQ("Ramon",metadatos.get("Propietario", "" ).asString());

}

TEST(baseDeDatos, alConsultarPorEtiquetaDeboRecibirElArchivoQuePoseeLaEtiqueta){

	string datosUsuario = cargarJsonUsuario();
	string datosArchivo = cargarJsonArchivo("Perez");

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Perez","MiClave",datosUsuario,800);
	
	base.agregarArchivo("Perez",datosArchivo,55);

	list<string> listaDeArchivos = base.buscarPorEtiquetas("Perez","Rojo");

	Json::Value metadatos;
	Json::Reader reader;

	reader.parse(listaDeArchivos.front(), metadatos);

	EXPECT_EQ("colores",metadatos.get("Nombre", "" ).asString());

}

TEST(baseDeDatos, alConsultarPorEtiquetaQueNoExisteNoDeboRecibirArchivos){

	string datosUsuario = cargarJsonUsuario();
	string datosArchivo = cargarJsonArchivo("Perez");

	BaseDeDatos base("testdb/");
	base.agregarUsuario("Perez","MiClave",datosUsuario,800);
	
	base.agregarArchivo("Perez",datosArchivo,55);

	list<string> listaDeArchivos = base.buscarPorEtiquetas("Perez","Pato");
	cout<<"SIZE  "<<listaDeArchivos.size()<<endl;

	EXPECT_EQ(listaDeArchivos.size(),0);

}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}
