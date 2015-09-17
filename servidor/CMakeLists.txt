#Nombre del proyecto y leguaje
project(servidor C CXX)

#Version minima para correr
cmake_minimum_required(VERSION 2.6)

#Se inclueyen todos los archivos de la carpeta clases
file(GLOB Clases 
	"clases/*.h"
	"clases/*.cpp"
)


#Incluyo el directorio para evitar poner la ruta entera por cada vez que se la usa
include_directories(clases bibliotecas/rocksdb/include bibliotecas/mongoose)

#Vincula los archivos al ejecutable
add_executable(servidor holaMundorRDB ${Clases} bibliotecas/mongoose/mongoose.c)

#Agrego biblioteca de rocksdb
add_library(rocksdb SHARED IMPORTED)
set_target_properties(rocksdb PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bibliotecas/rocksdb/librocksdb.a)
target_link_libraries(servidor rocksdb pthread rt snappy gflags z bz2)


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

#Se agrega el subdirectorio tests que tendra los tests a correr
add_subdirectory(tests)
