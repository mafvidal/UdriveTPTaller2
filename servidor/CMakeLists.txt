project(ejemplo C CXX) #Nombre del proyecto y lenguaje(CXX)

cmake_minimum_required(VERSION 2.6) #version minima para correr

include_directories(bibliotecas/rocksdb/include)


add_executable(ejemplo holaMundorRDB) #vincula el archivo hola.cpp al ejecutable


add_library(rocksdb SHARED IMPORTED)
set_target_properties(rocksdb PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/bibliotecas/rocksdb/librocksdb.a)
target_link_libraries(ejemplo rocksdb pthread rt snappy gflags z bz2)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

