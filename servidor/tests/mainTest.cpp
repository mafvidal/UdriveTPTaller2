#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include "BaseDeDatos.h"

TEST(Database, CreateOnOpen) {
	BaseDeDatos base("testdb/");
	base.setUsuario("Juan","ROCKSDB");
	EXPECT_TRUE(base.existeUsuario("Juan"));

}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
  	testing::InitGoogleMock(&argc, argv);
  	return RUN_ALL_TESTS();
}
