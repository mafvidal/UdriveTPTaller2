
# UdriveTPTaller2
##Descripcion

Este proyecto se desarrollo para la materia Taller de Programación II.

El mismo consiste en desarrollar una aplicación cliente-servidor para el almacenamiento remoto de archivos.

Esta aplicación consta de dos componentes:

* Un servidor, el cual será el responsable del procesamiento, almacenamiento y el delivery de las solicitudes de los usuarios.

* Un cliente, el cual será responsable de visualizar el almacenamiento remoto asociado al usuario que se encuentra conectado.

La comunicación cliente-servidor se realiza mediante Restful API.

Esta aplicación permite a cada cliente:

* Loguearse en el sistema.
* Almacenar sus archivos en un servidor remoto.
* Actualizar sus archivos.
* Compartir los archivos con otros usuarios.
* Descargar sus archivos.

Para el desarrollo, se debió cumplir con las siguientes restricciones:

* Desarrollar el servidor en C/C++.
* Desarrollar el cliente en Java utilizando el SDK de Android.
* Desarrollar el proyecto mediante integración continua, utilizando GitHub  y Travis CI
* Desplegar el servidor en Docker
* Realizar para el servidor pruebas unitarias, y tener un code coverage mayor al 71%.
* Utilizar como base de datos, para el servidor, RocksDB
* Realizar la documentación del proyecto con Sphinx

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

 - docker pull mafvidal/tp:v5

### Correr imagen

 - docker run -it mafvidal/tp:v5

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
