.. _descripcionDelProyecto:

Descripción del proyecto
========================

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
* Desarrollar el proyecto mediante integración continua, utilizando `GitHub <https://github.com/>`_ y `Travis CI <https://travis-ci.org/>`_
* Desplegar el servidor en `Docker <https://www.docker.com/>`_
* Realizar para el servidor pruebas unitarias, y tener un code coverage mayor al 71%.
* Utilizar como base de datos, para el servidor, `RocksDB <http://rocksdb.org/>`_
* Realizar la documentación del proyecto con `Sphinx <http://sphinx-doc.org/>`_
|
|
| :ref:`Volver a la pagina anterior <DocProyecto>`
| :ref:`Volver a la pagina principal <index>`
