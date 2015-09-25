#include <iostream>
#include <list>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BaseDeDatos.h"
#include "estructuras.h"
#include <fstream>
#include "json/json.h"

using namespace std;

TEST(baseDeDatos, existeUsuario) {
	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","ROCKSDB",800);
	EXPECT_TRUE(base.existeUsuario("Juan"));
}

TEST(baseDeDatos, verificarInexistenciaDeUsuario){
        BaseDeDatos base("testdb/");
        base.setUsuario("Juan","ROCKSDB",800);
        EXPECT_FALSE(base.existeUsuario("Roberto"));
}

TEST(baseDeDatos, verificarClaveCorrecta) {
	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","ROCKSDB",800);
	EXPECT_TRUE(base.esLaClaveCorrecta("Juan","ROCKSDB"));

}

TEST(baseDeDatos, verificarClaveIncorrecta) {
	BaseDeDatos base("testdb/");
	base.setUsuario("Pedro","123456",800);
	EXPECT_FALSE(base.esLaClaveCorrecta("Pedro","otraClave"));
}

TEST(baseDeDatos, almacenarDatosDeUnUsuarioExistenteYVerificarCorrectoAlmacenamiento){

	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","123456",800);

	//Cargo el json de prueba
	Json::Value root;
	Json::Reader reader;
	ifstream test("datosDeUsuario.json", ifstream::binary);
	reader.parse( test, root, false );

	base.setDatosUsuario("Juan",root.toStyledString());

	string datos = base.getDatosUsuario("Juan");

	reader.parse(datos, root);

	EXPECT_EQ("Juan",root.get("Nombre", "" ).asString());
	EXPECT_EQ("juan@gmail.com",root.get("Email", "" ).asString());
	EXPECT_EQ("juanFoto",root.get("Foto", "" ).asString());
	EXPECT_EQ("La Pampa",root.get("UltimaUbicacion", "" ).asString());

}

TEST(baseDeDatos, alAlmacenarUnArchivoEsteDebeEstarEnLaBase){
	
	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","123456",800);

	//Cargo el json de prueba
	Json::Value root;
	Json::Reader reader;
	ifstream test("datosDeUsuario.json", ifstream::binary);
	reader.parse( test, root, false );

	base.setDatosUsuario("Juan",root.toStyledString());
	
	ifstream test2("archivo.json", ifstream::binary);
	reader.parse( test2, root, false );
	
	base.agregarArchivo("Juan",root.toStyledString(),55);

	list<string> listaDeArchivos = base.getArchivos("Juan");

	reader.parse(listaDeArchivos.front(), root);

	EXPECT_EQ("colores",root.get("Nombre", "" ).asString());

}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}
