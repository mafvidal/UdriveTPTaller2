.. _Servidor:

Ejecutar servidor
=================

Debe acceder al directorio del servidor, ejecutando el siguiente comando:

.. code-block:: shell

	cd UdriveTPTaller2/servidor

Para compilar el proyecto deberá ejecutar los siguientes comandos:

.. code-block:: shell

	mkdir build
	cd build
	cmake ..
	make

Finalmente ejecute el servidor mediante el siguiente comando:

.. code-block:: shell

	./servidor

**Para finalizar el servidor precione la tecla "q" y enter**

Si desea guardar algun tipo de dato correspondiente al log:

Log Error:

.. code-block:: shell

	./servidor e

Log Info:

.. code-block:: shell

	./servidor i

Log Warn:

.. code-block:: shell

	./servidor w

Log Debug:

.. code-block:: shell

	./servidor d

Log Trace:

.. code-block:: shell

	./servidor t

|
|
| :ref:`Volver a la pagina anterior <ManAdministracion>`
| :ref:`Volver a la pagina principal <index>`
