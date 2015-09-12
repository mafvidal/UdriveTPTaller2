#Nombre del proyecto y leguaje
#project(ejemploRDB C CXX)

#Version minima para correr
#cmake_minimum_required(VERSION 2.6)

#Incluyo el directorio para evitar poner la ruta entera por cada vez que se la usa
#include_directories(bibliotecas/rocksdb/include)

#Vincula el archivo holaMundoRDB al ejecutable
#add_executable(ejemploRDB holaMundorRDB)

#Agrego biblioteca de rocksdb
#add_library(rocksdb SHARED IMPORTED)
#set_target_properties(rocksdb PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bibliotecas/rocksdb/librocksdb.a)
#target_link_libraries(ejemploRDB rocksdb pthread rt snappy gflags z bz2)


#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

#Se agrega el subdirectorio tests que tendra los tests a correr
add_subdirectory(tests)
