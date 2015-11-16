.. _InicioRapido:

Inicio rápido
=============

Para arrancar el servidor ejecute los siguientes pasos:

* Diríjase a la carpeta del proyecto, a través de la terminal.

* Compilar biblioteca RocksDB:

.. code-block:: bash

	cd servidor/bibliotecas/rocksdb/
	make static_lib
	
* Compilar Gtests:

.. code-block:: bash

	cd ..
	cd gmock/
	cmake .
	make

* Compilar el servidor:

.. code-block:: bash

	cd ../..
	mkdir build
	cd build/
	cmake ..
	make

* Arrancar servidor:

.. code-block:: bash

	./servidor

|
|
| :ref:`Volver a la pagina anterior <ManAdministracion>`
| :ref:`Volver a la pagina principal <index>`
