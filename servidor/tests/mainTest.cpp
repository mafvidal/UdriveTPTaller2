#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BaseDeDatos.h"

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

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
  	testing::InitGoogleMock(&argc, argv);
  	return RUN_ALL_TESTS();
}
