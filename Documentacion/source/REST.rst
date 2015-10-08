.. _REST:

Protocolo REST
==============

Registrar Usuario
+++++++++++++++++

URL: /users

TIPO: POST

BODY:

{

	"Usuario" : "fulanito15",

	"Clave" : "MiClave",

	"Cuota" : 800,

	"Nombre" : "Fulanito",

	"Email" : "``fulanitoMail@mail.com``",

	"Foto" : "FulanitoFoto",

	"UltimaUbicacion" : "La Pampa"

}

RESPONSE:

200 OK 	"Usuario creado exitosamente"
	"Usuario existente"
	 
Iniciar sesión
++++++++++++++
URL: /login

TIPO: GET

BODY:

{

	"Usuario" : "fulanito15",

	"Clave" : "MiClave",
}

RESPONSE:

200 OK 	"Inicio existoso"
401 	"No autorizado"

Agregar archivo
+++++++++++++++

URL:/files

TIPO: POST

BODY:

{

	"Usuario" : "fulanito15",

	"Espacio" : "50",

	"Metadatos" : {

		"Directorio" : "./documentos/",

		"Etiquetas" : [ "Rojo", "Azul", "Colores" ],

		"Extension" : "txt",

		"Nombre" : "colores",

		"Propietario" : "Fulanito15",

		"UltimaFechaModificacion" : "05/07/2009 06:55 p.m.",

		"UsuarioQueModifico" : "Fulanito15"

	}

}

RESPONSE:

200 OK 	"Creacion exitosa"

Eliminar archivo
++++++++++++++++

URL: /files

TIPO: DELETE

BODY:

{

	"Usuario" : "fulanito15",

	"Espacio" : "50",

	"Metadatos" : {

		"Directorio" : "./documentos/",

		"Etiquetas" : [ "Rojo", "Azul", "Colores" ],

		"Extension" : "txt",

		"Nombre" : "colores",

		"Propietario" : "Fulanito15",

		"UltimaFechaModificacion" : "05/07/2009 06:55 p.m.",

		"UsuarioQueModifico" : "Fulanito15"

	}

}

RESPONSE:

200 OK 	"Archivo eliminado"

Ver papelera
++++++++++++

URL: /deletedFiles

TIPO: GET

BODY:

{

	"Usuario" : "fulanito15"

}

RESPONSE:

200 OK 

[{

		"Directorio" : "./documentos/",

		"Etiquetas" : [ "Rojo", "Azul", "Colores" ],

		"Extension" : "txt",

		"Nombre" : "colores",

		"Propietario" : "Fulanito15",

		"UltimaFechaModificacion" : "05/07/2009 06:55 p.m.",

		"UsuarioQueModifico" : "Fulanito15"

}]

Eliminar archivo de la papelera
+++++++++++++++++++++++++++++++

URL: /deletedFiles

TIPO: DELETE

BODY:

{

	"Usuario" : "fulanito15",

	"Espacio" : "50",

	"Metadatos" : {

		"Directorio" : "./documentos/",

		"Etiquetas" : [ "Rojo", "Azul", "Colores" ],

		"Extension" : "txt",

		"Nombre" : "colores",

		"Propietario" : "Fulanito15",

		"UltimaFechaModificacion" : "05/07/2009 06:55 p.m.",

		"UsuarioQueModifico" : "Fulanito15"

	}

}

RESPONSE:

200 OK "Archivo eliminado"

|
|
| :ref:`Volver a la pagina anterior <DocTecnica>`
| :ref:`Volver a la pagina principal <index>`


