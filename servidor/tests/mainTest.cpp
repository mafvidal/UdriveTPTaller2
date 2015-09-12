#include <gtest/gtest.h>
#include <gmock/gmock.h>

//Test de prueba, para ver si compila y pasa 
TEST(Test, primerTest) {

	EXPECT_TRUE(true);

}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
  	testing::InitGoogleMock(&argc, argv);
  	return RUN_ALL_TESTS();
}
