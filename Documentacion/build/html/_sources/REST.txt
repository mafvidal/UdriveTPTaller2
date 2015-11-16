.. _REST:

API REST
========

En todos los mensajes, si el usuario en la url, no existe, el servidor enviara el siguiente mensaje:

.. code-block:: json

	{
		"Estado" : "ERROR",
		"Mensaje" : "El usuario no existe"
	}

Si la URL no es correcta, el servidor enviara el siguiente mensaje:

.. code-block:: json

	{
		"Estado" : "ERROR",
		"Mensaje" : "URL incorrecta"
	}

API REST Usuarios
-----------------

* :ref:`Usuarios <RAUsuarios>`

API REST Archivos logicos
-------------------------

* :ref:`Archivos logicos <RAArchivoslogicos>`

API REST Archivos Fisicos
-------------------------

* :ref:`Archivos Fisicos <RAArchivosFisicos>`

API REST Busquedas
------------------

* :ref:`Busquedas <RABusquedas>`

|
|
| :ref:`Volver a la pagina anterior <DocTecnica>`
| :ref:`Volver a la pagina principal <index>`


