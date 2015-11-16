.. _Tests:

Correr Pruebas
==============

**Para correr cualquier test primero debe eliminar las base de datos generada por los tests anteriores.**

Para correr los tests de la base de datos, debe acceder al directorio del servidor, ejecutando el siguiente comando:

.. code-block:: shell

	cd UdriveTPTaller2/servidor

Si el servidor no fue compilado deberá ejecutar los siguientes comandos:

.. code-block:: shell

	mkdir build
	cd build
	cmake ..
	make

Finalmente ejecute los tests mediante los siguientes comandos:

.. code-block:: shell

	cd tests
	./tests

Para correr los test rest, debe acceder al directorio del servidor, ejecutando el siguiente comando:

.. code-block:: shell

	cd UdriveTPTaller2/servidor

Si el servidor no fue compilado deberá ejecutar los siguientes comandos:

.. code-block:: shell

	mkdir build
	cd build
	cmake ..
	make

Luego ejecute el servidor, mediante el siguiente comando:

.. code-block:: shell

	./servidor

Despues debe ir a la carpeta donde se encuentra el archivo de test, en la carpeta tests, ejecutando los siguientes comandos:

.. code-block:: shell

	cd ..
	cd tests

Finalmente corra los tests con el siguiente comando:

.. code-block:: shell

	python testsServidor.py

|
|
| :ref:`Volver a la pagina anterior <ManAdministracion>`
| :ref:`Volver a la pagina principal <index>`

