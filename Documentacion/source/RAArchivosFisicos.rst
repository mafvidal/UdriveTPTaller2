.. _RAArchivosFisicos:

API REST Archivos Fisicos
=========================

Agregar archivo
+++++++++++++++

Permite agregar un archivo fisicamente, la URL debe incluir la ID recibida al crear el archivo.

**URL**: /usuarios/nombreUsuario/archivofisico/IDArchivo

**TIPO**: POST

**BODY**:

Archivo a guardar

**Salida**:

*Si se guardo el archivo exitosamente*:

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "Archivo creado correctamente"
	}

*Si la ID no pertenece a un archivo*:

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo no existe"
	}

Actualizar archivo
++++++++++++++++++

Permite actuaizar un archivo fisicamente, la URL debe incluir la ID recibida al actualizar el archivo.

**URL**: /usuarios/nombreUsuario/archivofisico/IDArchivo

**TIPO**: PUT

**BODY**:

Archivo a actualizar

**Salida**:

*Si se guardo el archivo exitosamente*:

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "Archivo creado correctamente"
	}

*Si la ID no pertenece a un archivo*:

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo no existe"
	}

Descargar archivo
+++++++++++++++++

Permite al usuario descargar un determinado archivo.

**URL**: /usuarios/nombreUsuario/archivofisico/IDArchivo/

**TIPO**: GET

**Salida**:

*Si el archivo existe*:

* El archivo fisico.

*Si el archivo no existe*:

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo no se pudo abrir"
	}

Descargar version del archivo
+++++++++++++++++++++++++++++

Permite al usuario descargar un determinado archivo.

**URL**: /usuarios/nombreUsuario/archivofisico/IDArchivo/NumeroDeVersion

**TIPO**: GET

**Salida**:

*Si el archivo existe*:

* El archivo fisico.

*Si la version no existe*:

* retorna la version actual del archivo.

*Si el archivo no existe*:

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo no se pudo abrir"
	}


Subir foto del usuario
++++++++++++++++++++++

Permite al usuario subir su foto.

**URL**: /usuarios/nombreUsuario/foto

**TIPO**: POST

**BODY**:

* Foto del usuario

**Salida**:

*Si se guardo la foto exitosamente*:

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "Archivo creado correctamente"
	}

*Si el usuario no existe*:

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El usuario no existe"
	}

Descargar foto del usuario
++++++++++++++++++++++++++

Permite al usuario descargar su foto.

**URL**: /usuarios/nombreUsuario/foto

**TIPO**: GET

**Salida**:

*Si la foto existe*:

* La foto del usuario.

*Si el usuario no guardo una foto*:

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo no existe"
	}


|
|
| :ref:`Volver a la pagina anterior <REST>`
| :ref:`Volver a la pagina principal <index>`


