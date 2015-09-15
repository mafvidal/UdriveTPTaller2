# UdriveTPTaller2
Repositorio para el grupo de taller de programación 2

##Instalacion general

  sudo apt-get install cmake

## Servidor

#### rocksdb

##### Instalar bibliotecas:

 - sudo apt-get install libsnappy-dev
 - sudo apt-get install libgflags-dev
 - sudo apt-get install zlib1g-dev
 - sudo apt-get install libbz2-dev

##### Compilar rocksdb:

###### En la carpeta servidor/bibliotecas/rocksdb

 - make static_lib

##### Compilar y ejecutar el "holaMundorRDB.cpp":

###### En la carpeta servidor/

 - mkdir build
 - cd build
 - cmake ..
 - make
 - ./ejemplo

#### GTest y GMock

##### Compilar GTest y GMock:

###### En la carpeta servidor/bibliotecas/gmock:

 - cmake .
 - make

##### Correr test

###### En la carpeta servidor/build

 - cmake ..
 - make
 - cd tests
 - ./tests
