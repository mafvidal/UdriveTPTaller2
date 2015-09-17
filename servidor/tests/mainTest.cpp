#include <iostream>
#include <list>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BaseDeDatos.h"
#include "estructuras.h"

using namespace std;

TEST(baseDeDatos, existeUsuario) {
	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","ROCKSDB");
	EXPECT_TRUE(base.existeUsuario("Juan"));
}

TEST(baseDeDatos, verificarInexistenciaDeUsuario){
        BaseDeDatos base("testdb/");
        base.setUsuario("Juan","ROCKSDB");
        EXPECT_FALSE(base.existeUsuario("Roberto"));
}

TEST(baseDeDatos, verificarClaveCorrecta) {
	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","ROCKSDB");
	EXPECT_TRUE(base.esLaClaveCorrecta("Juan","ROCKSDB"));

}

TEST(baseDeDatos, verificarClaveIncorrecta) {
	BaseDeDatos base("testdb/");
	base.setUsuario("Pedro","123456");
	EXPECT_FALSE(base.esLaClaveCorrecta("Pedro","otraClave"));
}
TEST(baseDeDatos, almacenarDatosDeUnUsuarioExistente){
	BaseDeDatos base("testdb/");
	base.setUsuario("Pedro","123456");
	base.setDatosUsuario("Pedro","Pedro,pedro@mail.com");
	EXPECT_EQ(base.getDatosUsuario("Pedro"),"Pedro,pedro@mail.com");

}

TEST(baseDeDatos, obtenerArchivoGuardado){
	BaseDeDatos base("testdb/");
	base.setUsuario("Pedro","123456");
	base.agregarArchivo("Pedro","documentos/hola.txt");
	list<Archivo> archivos = base.getArchivos("Pedro");
	EXPECT_EQ(archivos.front().nombre,"hola.txt");
}

TEST(baseDeDatos, obtenerDirectorioGuardado){
	BaseDeDatos base("testdb/");
	base.setUsuario("Luis","123456");
	base.agregarArchivo("Luis","documentos/hola.txt");
	list<Archivo> archivos = base.getArchivos("Luis");
	EXPECT_EQ(archivos.front().directorio,"documentos/");
}

TEST(baseDeDatos, obtenerCorrectamenteDosArchivosIngresados){

	BaseDeDatos base("testdb/");
	base.setUsuario("Carlos","123456");
	base.agregarArchivo("Carlos","documentos/hola.txt");
	base.agregarArchivo("Carlos","./chau.txt");
	list<Archivo> archivos = base.getArchivos("Carlos");
	EXPECT_EQ(archivos.front().nombre,"hola.txt");
	EXPECT_EQ(archivos.back().nombre,"chau.txt");

}

TEST(baseDeDatos, siNoIngresoArchivosDeboRecibirListaVaciaAlPedirListaDeArchivos){

	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","123456");
	list<Archivo> archivos = base.getArchivos("Juan");
	EXPECT_EQ(archivos.size(),0);

}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}
