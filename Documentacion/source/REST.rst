.. _REST:

Protocolo REST
==============

Registrarse
+++++++++++

Permite al usuario registrarse en el sistema 

URL: /usuarios/nombreUsuario

TIPO: POST

BODY:

	{

	"Cuota" : "800",

	"Clave" : "MiClave",

    	"MetaDatos" : {
    
    		"Email" : "fulanitoMail@mail.com",
    	
    		"Foto" : "FulanitoFoto",
    	
    		"Nombre" : "Fulanito",
    	
    		"UltimaUbicacion" : "Bs As"
    
    		}

	}

Salida:

* "OK" "Usuario creado exitosamente"
* "ERROR" "Error usuario existente" 
	 
Iniciar sesión
++++++++++++++

URL: /iniciarsesion/nombreUsuario

TIPO: POST

BODY:

	{

		"Clave" : "MiClave"
	}

Salida:

* "OK" "Inicio existoso"
* "ERROR" "Usuario o clave incorrecta"

Obtener datos del usuario
+++++++++++++++++++++++++

Retorna los datos del usuario

URL: /usuarios/nombreUsuario

TIPO: GET

Salida:

	"OK"

	{
    
    		"Email" : "fulanitoMail@mail.com",
    	
    		"Foto" : "FulanitoFoto",
    	
    		"Nombre" : "Fulanito",
    	
    		"UltimaUbicacion" : "Bs As"
    
    	}



Actualizar datos del usuario
++++++++++++++++++++++++++++

Permite al usuario actualizar sus datos, como la clave, la cuota asignada, etc

URL: /usuarios/nombreUsuario/archivos

TIPO: POST

BODY:

	{

	"Cuota" : "800",

	"Clave" : "otraClave",

    	"MetaDatos" : {
    
    		"Email" : "fulanitoMail@mail.com",
    	
    		"Foto" : "FulanitoFoto",
    	
    		"Nombre" : "Fulanito",
    	
    		"UltimaUbicacion" : "Bs As"
    
    		}

	}

Salida:

* "OK" 	"datos actualizados correctamente"

Crear archivo
+++++++++++++

Permite almacenar los metadatos del archivo en la base de datos

URL: /usuarios/nombreUsuario/archivos

TIPO: POST

BODY:

	{
    	  "Directorio" : "./documentos/",
    	  "Etiquetas" : [ "Rojo", "Azul", "Colores" ],
    	  "Extension" : "txt",
    	  "Nombre" : "colores"
	}

Salida:

* "OK" 	"Archivo creado correctamente"
* "ERROR" "No se pudo crear el archivo" 


Obtener archivos
++++++++++++++++

Devuelve los archivos para un determinado usuario

URL: /usuarios/nombreUsuario/archivos

TIPO: POST

Salida:

	"OK"

	[
		{

			"Directorio" : "./documentos/",

			"Etiquetas" : [ "Rojo", "Azul", "Colores" ],

			"Extension" : "txt",

			"Nombre" : "colores",

			"Propietario" : "Fulanito15",

			"UltimaFechaModificacion" : "05/07/2009 06:55 p.m.",

			"UsuarioQueModifico" : "Fulanito15"

		}

		.

		.

		.
	]

Eliminar archivos
+++++++++++++++++

Permite eliminar un determinado archivo

URL: /usuarios/nombreUsuario/archivos

TIPO: DELETE

BODY:

	{
    	  "Propietario" : "Fulanito",
    	  "Directorio" : "./documentos/",
    	  "Extension" : "txt",
    	  "Nombre" : "colores"
	}

Salida:

* "OK" 	"Archivo enviado a la papelera"

Compartir archivos
++++++++++++++++++

Permite compartir archivos con una lista de usuarios determinada

URL: /usuarios/nombreUsuario/archivos/compartir

TIPO: PUT

BODY:

	{
    	  "Usuarios" : ["usuario1","usuario2"],
    	  "Propietario" : "Fulanito",
    	  "Directorio" : "./documentos/",
    	  "Extension" : "txt",
    	  "Nombre" : "colores"
	}

Salida:

* "OK" 	"El archivo fue compartido"

Buscar por metadato
+++++++++++++++++++

Permite buscar archivos por un determinado metadato

URL: /usuarios/nombreUsuario/archivos/tipoMetadato/nombreMetadato

tipoMetadato: (etiquetas,nombre,propietario,extension)

TIPO: GET

Salida:

	"OK"
	[
		{

			"Directorio" : "./documentos/",

			"Etiquetas" : [ "Rojo", "Azul", "Colores" ],

			"Extension" : "txt",

			"Nombre" : "colores",

			"Propietario" : "Fulanito15",

			"UltimaFechaModificacion" : "05/07/2009 06:55 p.m.",

			"UsuarioQueModifico" : "Fulanito15"

		}

		.

		.

		.
	]

Actualizar archivos
===================

Permite actualizar los metadatos del archivo, segun los datos enviados

URL: /usuarios/nombreUsuario/archivos/actualizar

TIPO: PUT

BODY:

	{

		"Propietario" : "Fulanito15",

		"DirectorioOriginal" : "./documentos/",

		"ExtensionOriginal" : "txt",

		"NombreOriginal" : "colores",

		"DirectorioNuevo" : "./doc/",

		"ExtensionNuevo" : "bat",

		"NombreNuevo" : "masColores",

		"Etiquetas" : [ "Rojo", "Azul", "Colores" ],

		"EtiquetasAgregadas" : [ "Azul" ],

		"EtiquetasEliminadas" : [ "Color" ],

		"FechaModificacion" : "05/07/2009 06:55 p.m.",

		"UsuarioQueModifico" : "Fulanito15"

	}

Salida:

* "OK" "Archivo actualizado"

Restaurar archivos
===================

Permite restaurar los metadatos del archivo, a la version anterior

URL: /usuarios/nombreUsuario/archivos/restaurar

TIPO: PUT

BODY:
 
	{

		"Directorio" : "./documentos/",

		"Extension" : "txt",

		"Nombre" : "colores",

		"Propietario" : "Fulanito15",

		"UltimaFechaModificacion" : "05/07/2009 06:55 p.m.",

		"UsuarioQueModifico" : "Fulanito15"

	}

Salida:

* "OK" "Archivo restaurado"


|
|
| :ref:`Volver a la pagina anterior <DocTecnica>`
| :ref:`Volver a la pagina principal <index>`


