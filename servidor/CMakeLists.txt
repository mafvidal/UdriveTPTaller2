#Nombre del proyecto y leguaje
project(servidor C CXX)

#Version minima para correr
cmake_minimum_required(VERSION 2.6)

#Se inclueyen todos los archivos de la carpeta clases
file(GLOB Clases 
	"clasesCP2/*.h"
	"clasesCP2/*.cpp"
)


#Incluyo el directorio para evitar poner la ruta entera por cada vez que se la usa
include_directories(clasesCP2 bibliotecas/rocksdb/include bibliotecas/mongoose bibliotecas/JsonCpp)

#Vincula los archivos al ejecutable
add_executable(servidor main ${Clases} bibliotecas/mongoose/mongoose.c bibliotecas/JsonCpp/jsoncpp.cpp)

#Agrego biblioteca de rocksdb
add_library(rocksdb SHARED IMPORTED)
set_target_properties(rocksdb PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bibliotecas/rocksdb/librocksdb.a)
target_link_libraries(servidor rocksdb pthread rt snappy gflags z bz2)


set(CMAKE_CXX_FLAGS "-std=c++11  -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-DMG_ENABLE_THREADS")

#Se agrega el subdirectorio tests que tendra los tests a correr
add_subdirectory(tests)
