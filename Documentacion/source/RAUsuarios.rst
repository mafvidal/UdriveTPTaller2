.. _RAUsuarios:

API REST Usuarios
=================

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


|
|
| :ref:`Volver a la pagina anterior <REST>`
| :ref:`Volver a la pagina principal <index>`


