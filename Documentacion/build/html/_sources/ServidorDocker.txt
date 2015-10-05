.. _ServidorDocker:

Ejecutar el servidor en Docker
==============================

Para ejecutar el servidor en Docker, debe :ref:`instalar Docker <InstalarDocker>`

Una vez instalado Docker, deberá descargar la imagen que contiene el servidor, ejecutando el siguiente comando en la terminal:

* docker pull mafvidal/tp:v3

Luego deberá ejecutar la imagen mediante el siguiente comando:

* docker run -it mafvidal/tp:v3

Debe acceder al directorio que contiene el ejecutable del servidor, ejecutando el siguiente comando:

* cd home/proyectoTaller2/UdriveTPTaller2/servidor/build

Finalmente, ejecute el servidor mediante el siguiente comando:

* ./servidor

Si desea correr los test deberá ejecutar los siguientes comandos:

* cd home/proyectoTaller2/UdriveTPTaller2/servidor/build/tests
* ./test
|
|
| :ref:`Volver a la pagina anterior <ManAdministracion>`
| :ref:`Volver a la pagina principal <index>`
