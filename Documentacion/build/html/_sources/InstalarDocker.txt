.. _InstalarDocker:


Instalar Docker
===============

Para instalar Docker primero debe tener instalado curl, para comprobar si curl esta instalado ejecute el siguiente comando en la terminal:

* which curl

Si luego de ejecutar el comando anterior, no aparece el directorio donde tiene instalado curl, deberá ejecutar los siguientes comandos, en la terminal, para la instalación de curl:

* sudo apt-get update
* sudo apt-get install curl

Para instalar Docker, deberá ejecutar el siguiente comando en la terminal:

* curl -sSL ``https://get.docker.com/`` | sh

Puede comprobar si Docker se instalo correctamente ejecutando el siguiente comando en la terminal:

* sudo docker run hello-world
|
|
| :ref:`Volver a la pagina anterior <Configuracion>`
| :ref:`Volver a la pagina principal <index>`
