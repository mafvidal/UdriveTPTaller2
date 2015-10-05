
# UdriveTPTaller2
Repositorio para el grupo de taller de programación 2

##Instalacion general

 - sudo apt-get install cmake
 - sudo apt-get install g++

### Instalar Docker
#### Comprobar Curl

 - which curl

##### Si no existe

 - sudo apt-get update
 - sudo apt-get install curl

#### Obtener ultimo paquete de Docker

 - curl -sSL https://get.docker.com/ | sh
 
#### Probar Docker

 - sudo docker run hello-world

#### Descargar imagen con este repo de dockerHub(Hasta commit 48)

 - docker pull mafvidal/tp:v3

### Correr imagen

 - docker run -it mafvidal/tp:v1

### Ver el repo en la imagen

 - cd home/proyectoTaller2/UdriveTPTaller2

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
 - ./servidor

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

##Ver documentacion

Para ver la documentacion debe acceder a la carpera: Documentacion/build/html, y ejecutar el archivo index.html
