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

Registrarse
+++++++++++

Permite al usuario registrarse en el sistema 

**URL**: /usuarios/nombreUsuario

**TIPO**: POST

Recibe en un json la cuota asignada, la clave del usuario, y sus metadatos; email, nombre del usuario, nombre de la foto, ultima ubicación.

**BODY**

.. code-block:: json

	{
		"Cuota" : 800,
		"Clave" : "MiClave",
		"MetaDatos" : {
			"Email" : "miMail@mail.com",
			"Foto" : "miFoto",
			"Nombre" : "Fulanito",
			"UltimaUbicacion" : "Bs As"
		}
	}


**Salida**:

*Registro exitoso:*

.. code-block:: json

	{
		"Estado" : "OK",
		"Mensaje" : "Se registro correctamente el usuario"
	}

*Ya existe el usuario:*

.. code-block:: json

	{
		"Estado" : "ERROR",
		"Mensaje" : "Error usuario existente"
	}

	 
Iniciar sesión
++++++++++++++

Permite al usuario iniciar sesión en el sistema

**URL**: /iniciarsesion/nombreUsuario

**TIPO**: POST

Se envia en el json la clave del usuario

**BODY**:

.. code-block:: json

	{
		"Clave" : "MiClave"
	}

**Salida**:

*Inicio de sesion exitoso*:

.. code-block:: json

	{
		"Estado" : "OK",
		"Mensaje" : "Inicio existoso"
	}

*Clave o nombre de usuario incorrecto*:

.. code-block:: json

	{
		"Estado" : "ERROR",
		"Mensaje" : "Usuario o clave incorrecta"
	}

Obtener datos del usuario
+++++++++++++++++++++++++

Retorna los datos del usuario

**URL**: /usuarios/nombreUsuario

**TIPO**: GET

**Salida**:

.. code-block:: json

	{
		"Email": "miMail@mail.com",
		"Foto": "miFoto",
		"Nombre": "Fulanito",
		"UltimaUbicacion": "Bs As",
		"Estado": "OK"
	}


Actualizar datos del usuario
++++++++++++++++++++++++++++

Permite al usuario actualizar sus datos, como la clave, la cuota asignada, nombre, ultima ubicacion.

**URL**: /usuarios/nombreUsuario

**TIPO**: PUT

Se le envian al usuario los datos actualizados

**BODY**:

.. code-block:: json

	{
		"Cuota" : 1000,
		"Clave" : "otraClave",
		"MetaDatos" : {
			"Email" : "fulanitoMail@mail.com",
			"Foto" : "OtraFoto",
			"Nombre" : "Fulanito",
			"UltimaUbicacion" : "Corrientes"
		}
	}

**Salida**:

.. code-block:: json

	{
		"Estado": "OK",
		"Mensaje": "datos actualizados correctamente"
	}

Agregar archivo al usuario (*Solo los metadatos*)
+++++++++++++++++++++++++++++++++++++++++++++++++

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

Obtener los archivos del usuario (*Solo los metadatos*)
+++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

Obtener los archivos compartidos con el usuario (*Solo los metadatos*)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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


Ver archivos en la papelera (Solo metadatos)
++++++++++++++++++++++++++++++++++++++++++++

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

Actualizar archivo (Solo los metadatos)
+++++++++++++++++++++++++++++++++++++++

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
		"Mensaje": "Archivo restaurado"
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

Buscar por metadato
+++++++++++++++++++

Buscar por etiquetas
--------------------

Permite buscar los archivos por una determinada etiqueta

**URL**: /usuarios/nombreUsuario/archivos/etiquetas/nombreDeLaEtiqueta

**TIPO**: GET

Buscar por propietario
----------------------

Permite buscar los archivos que pertenecen al propietario indicado

**URL**: /usuarios/nombreUsuario/archivos/propietario/nombreDelPropietario

**TIPO**: GET

Buscar por nombre
-----------------

Permite buscar los archivos que poseen el nombre indicado

**URL**: /usuarios/nombreUsuario/archivos/nombre/nombreDelArchivo

**TIPO**: GET

Buscar por extension
--------------------

Permite buscar los archivos que poseen extension indicada

**URL**: /usuarios/nombreUsuario/archivos/nombre/extensionDelArchivo

**TIPO**: GET

*Para todas las busquedas por metadatos la salida es la siguiente*
------------------------------------------------------------------

**Salida**:

.. code-block:: json

	{
		"Archivos": [
			{
				"Directorio": "/documentos/mae/",
				"Etiquetas": ["Rojo","Azul","Colores"],
				"Extension": "pdf",
				"FechaDeModificacion": "11/12/15 02:35:32 PM",
				"ID": "4106985908",
				"Nombre": "tp",
				"Propietario": "pepe1",
				"UsuarioQueModifico": "pepe1",
				"Version": 0
			}
		],
		"Estado": "OK"
	}

Agregar archivo (Fisicamente)
+++++++++++++++++++++++++++++

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

Actualizar archivo (fisicamente)
++++++++++++++++++++++++++++++++

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

Descargar archivo (fisicamente)
+++++++++++++++++++++++++++++++

Permite al usuario descargar un determinado archivo.

**URL**: /usuarios/nombreUsuario/archivofisico/IDArchivo

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



|
|
| :ref:`Volver a la pagina anterior <DocTecnica>`
| :ref:`Volver a la pagina principal <index>`


