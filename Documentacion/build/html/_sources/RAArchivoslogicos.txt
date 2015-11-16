.. _RAArchivoslogicos:

API REST Archivos logicos
=========================

Agregar archivo al usuario
++++++++++++++++++++++++++

Permite almacenar los metadatos del archivo en la base de datos, y retorna la ID del archivo, para agregarlo físicamente.

**URL**: /usuarios/nombreUsuario/archivos

**TIPO**: POST

Se le envia en un json, el nombre del archivo, la extension, el directorio, las etiquetas y el tamaño del archivo.

**BODY**:

.. code-block:: json

	{
		"Espacio" : 100,
		"Directorio" : "/documentos/Taller2/",
		"Etiquetas" : [ "Taller2", "Informe", "Checkpoint" ],
		"Extension" : "pdf",
		"Nombre" : "tp"
	}

**Salida**:

*Si se creeo correctamente el archivo*

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "IDARCHIVO"
	}

*Si el tamaño del archivo es mayor a la cuota disponible del usuario*

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo supera el limite de cuota"
	}

Obtener los archivos del usuario
++++++++++++++++++++++++++++++++

Devuelve solo los metadatos de los archivos, de los cuales el usuario es propietario.

**URL**: /usuarios/nombreUsuario/archivos

**TIPO**: GET

**Salida**:

.. code-block:: json

	{
		"Archivos": [
			{
				"Directorio": "/documentos/mae/",
				"Etiquetas": [ "Rojo", "Azul", "Colores" ],
				"Extension": "pdf",
				"FechaDeModificacion": "",
				"ID": "4106985908",
				"Nombre": "tp",
				"Propietario": "pepe1",
				"UsuarioQueModifico": "",
				"Version": 0
			},
			{
				"Directorio": "/doc/",
				"Etiquetas": [ "Rojo", "Marron", "Colores" ],
				"Extension": "docx",
				"FechaDeModificacion": "11/12/15 02:00:50 PM",
				"ID": "2426313491",
				"Nombre": "TrabajoPractico",
				"Propietario": "pepe1",
				"UsuarioQueModifico": "pepe2",
				"Version": 1
			    }
		],
		"Estado": "OK"
	}

Obtener los archivos compartidos con el usuario
+++++++++++++++++++++++++++++++++++++++++++++++

Devuelve solo los metadatos de los archivos, los cuales fueron compartidos con el usuario.

**URL**: /usuarios/nombreUsuario/archivoscompartidos

**TIPO**: GET

**Salida**:

.. code-block:: json

	{
		"Archivos": [
			{
				"Directorio": "/doc/",
				"Etiquetas": [ "Rojo", "Marron", "Colores" ],
				"Extension": "docx",
				"FechaDeModificacion": "11/12/15 02:00:50 PM",
				"ID": "2426313491",
				"Nombre": "TrabajoPractico",
				"Propietario": "pepe1",
				"UsuarioQueModifico": "pepe2",
				"Version": 1
			    }
		],
		"Estado": "OK"
	}

Enviar archivo a la papelera 
++++++++++++++++++++++++++++

Permite enviar un archivo a la papelera.

**URL**: /usuarios/nombreUsuario/archivos

**TIPO**: DELETE

Se le envia en un json el propietario(su usuario), el directorio , la extension y el nombre del archivo.

**BODY**:

.. code-block:: json

	{
		"Propietario" : "pepe1",
		"Directorio" : "/documentos/mae/",
		"Extension" : "pdf",
		"Nombre" : "tp"
	}

**Salida**:

*Si se elimina correctamente el archivo*

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "Archivo enviado a la papelera"
	}

*Si el archivo ya se encuentra en la papelera*

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo ya se encuentra en la papelera"
	}


Ver archivos en la papelera
+++++++++++++++++++++++++++

Retorna los metadatos de los archivos que se encuentran en la papelera.

**URL**: /usuarios/nombreUsuario/papelera

**TIPO**: GET

**Salida**:

.. code-block:: json

	{
		"Archivos": [
			{
				"Directorio": "/doc/",
				"Etiquetas": [ "Rojo", "Marron", "Colores" ],
				"Extension": "docx",
				"FechaDeModificacion": "11/12/15 02:00:50 PM",
				"ID": "2426313491",
				"Nombre": "TrabajoPractico",
				"Propietario": "pepe1",
				"UsuarioQueModifico": "pepe2",
				"Version": 1
			    }
		],
		"Estado": "OK"
	}


Recuperar archivo de la papelera
++++++++++++++++++++++++++++++++

Retorna los metadatos de los archivos que se encuentran en la papelera.

**URL**: /usuarios/nombreUsuario/archivos/recuperar

**TIPO**: PUT

Recibe un json, con el directorio, extension, nombre, y propietario del archivo.

**BODY**:

.. code-block:: json

	{
		"Directorio" : "/documentos/mae/",
		"Propietario" : "pepe1",
		"Extension" : "pdf",
		"Nombre" : "tp"
	}

**Salida**:

*Si el archivo se encuentra en la papelera*

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "Archivo recuperado"
	}

*Si el archivo no se encuentra en la papelera*

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo no fue eliminado"
	}

Actualizar archivo
++++++++++++++++++

Permite actualizar los metadatos del archivo, y retorna la ID del archivo para actualizarlo fisicamente.

**URL**: /usuarios/nombreUsuario/archivos/actualizar

**TIPO**: PUT

Recibe un json, con el directorio, extension y nombre original, y los nuevos. Ademas recibe, el propietario, las etiquetas, las etiquetas agregadas y eliminadas.

**BODY**:

.. code-block:: json

	{
		"Propietario" : "pepe1",
		"DirectorioOriginal" : "/documentos/mae/",
		"ExtensionOriginal" : "pdf",
		"NombreOriginal" : "tp",
		"DirectorioNuevo" : "/doc/",
		"ExtensionNueva" : "docx",
		"NombreNuevo" : "TrabajoPractico",
		"Etiquetas" : [ "Rojo", "Marron", "Colores" ],
		"EtiquetasNuevas" : [ "Marron" ],
		"EtiquetasEliminadas" : [ "Azul" ]
	}

**Salida**:

*Si el archivo fue actualizado con exito*

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "IDARCHIVO"
	}

*Si el archivo no existe*

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "No existe el archivo a actualizar"
	}

Restaurar archivo
+++++++++++++++++

Restaura el archivo, deshaciendo la ultima actualización.

**URL**: /usuarios/nombreUsuario/archivos/restaurar

**TIPO**: PUT

Recibe un json, con el directorio, extension, nombre y propietario del archivo.

**BODY**:

.. code-block:: json

	{
		  "Directorio" : "/documentos/mae/",
		  "Propietario" : "pepe1",
		  "Extension" : "pdf",
		  "Nombre" : "tp"
	}

**Salida**:

*Si el archivo fue restaurado con exito*

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "IDArchivo"
	}

*Si el archivo no existe*

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo a restaurar no existe"
	}

*Si el archivo nunca fue actualizado*

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "No existe una version del archivo a restaurar"
	}


Compartir archivos
++++++++++++++++++

Permite compartir archivos con una lista de usuarios determinada.

**URL**: /usuarios/nombreUsuario/archivos/compartir

**TIPO**: PUT

Recibe en un json, los usuarios con lo que se va a compartir el archivo, y el directorio, propietario, nombre y extension del archivo a compartir

**BODY**:

.. code-block:: json

	{
		"Usuarios" : ["pepe2","pepe3"],
		"Directorio" : "/documentos/mae/",
		"Propietario" : "pepe1",
		"Extension" : "pdf",
		"Nombre" : "tp"
	}

**Salida**:

*Si el archivo es compartido con exito*

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "El archivo fue compartido"
	}

*Si el archivo no existe*

.. code-block:: json

	{
		"Estado": "ERROR",
		"Mensaje": "El archivo a compartir no existe"
	}

*Si alguno de los usuarios a compartir no existe*

.. code-block:: json

	{
		"Estado": "WARNIG",
		"Mensaje": "Los ususarios: pepe3 no existen"
	}


|
|
| :ref:`Volver a la pagina anterior <REST>`
| :ref:`Volver a la pagina principal <index>`


