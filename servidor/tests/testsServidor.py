#! /usr/bin/python

import requests
import unittest

class TestServidor(unittest.TestCase):

	def test_01registrarUsuarioCorrectamente(self):

		#No le envio los metadatos del usuario, para simplificar el tests
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500'}
		#Registro el usuario
		salida = requests.post('http://localhost:8000/usuarios/usu1', json=registrarUsuarioJson)
		salidaJson = salida.json()
		self.assertEqual("Se registro correctamente el usuario", salidaJson["Mensaje"])
		self.assertEqual("OK", salidaJson["Estado"])

	def test_02iniciarSesionUsuarioCorrectamente(self):

		iniciarSesionJson = {'Clave': 'MiClave'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500'}
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu2', json=registrarUsuarioJson)
		#Inicio sesion con el usuario
		salida = requests.post('http://localhost:8000/iniciarsesion/usu2', json=iniciarSesionJson)
		salidaJson = salida.json()
		self.assertEqual("Inicio existoso", salidaJson["Mensaje"])
		self.assertEqual("OK", salidaJson["Estado"])

	def test_03iniciarSesionUsuarioConClaveIncorrectaReciboError(self):

		iniciarSesionJson = {'Clave': 'otraClave'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500'}
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu3', json=registrarUsuarioJson)
		#Inicio sesion con el usuario
		salida = requests.post('http://localhost:8000/iniciarsesion/usu3', json=iniciarSesionJson)
		salidaJson = salida.json()
		self.assertEqual("Usuario o clave incorrecta", salidaJson["Mensaje"])
		self.assertEqual("ERROR", salidaJson["Estado"])

	def test_04registrarUsuarioExistenteReciboQueElUsuarioYaExiste(self):

		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500'}
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu1', json=registrarUsuarioJson)
		salidaJson = salida.json()
		self.assertEqual("Error usuario existente", salidaJson["Mensaje"])
		self.assertEqual("ERROR", salidaJson["Estado"])

	def test_05ObtenerDatosUsuarioRegistrado(self):

		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu5', json=registrarUsuarioJson)
		#Obtengo los datos del usuario
		salida = requests.get('http://localhost:8000/usuarios/usu5')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("pepe@mail.com", salidaJson["Datos"]["Email"])

	def test_06ActualizarDatosUsuario(self):
	
		#Metadatos originales
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		#Metadatos para actualizar
		MetaDatosActualizados = {'Email': 'pepito@mail.com','Foto': 'otraFoto','Nombre': 'carlos','UltimaUbicacion': 'China'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		actualizarUsuarioJson = {'Clave': 'otraClave','Cuota': '100500','MetaDatos': MetaDatosActualizados }
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu6', json=registrarUsuarioJson)
		#Se actualizan los datos del usuario
		salida = requests.put('http://localhost:8000/usuarios/usu6', json=actualizarUsuarioJson)
		#Se obtienen los datos del usuario
		salida = requests.get('http://localhost:8000/usuarios/usu6')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("pepito@mail.com", salidaJson["Datos"]["Email"])
		self.assertEqual("otraFoto", salidaJson["Datos"]["Foto"])
		self.assertEqual("China", salidaJson["Datos"]["UltimaUbicacion"])

	def test_07AlCrearArchivoElUsuarioDebeTenerlo(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu7','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu7', json=registrarUsuarioJson)
		#Se crea el archivo
		salida = requests.post('http://localhost:8000/usuarios/usu7/archivos', json=archivoJson)
		#Se obtiene el archivo del usuario
		salida = requests.get('http://localhost:8000/usuarios/usu7/archivos')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("usu7", salidaJson["Datos"][0]["Propietario"])
		self.assertEqual("hola", salidaJson["Datos"][0]["Nombre"])

	def test_08AlEliminarArchivoEsteDebeEstarEnLaPapelera(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu8','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		#Datos necesarios para eliminar archivo
		eliminarArchivoJson = {'Propietario': 'usu8','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin' }
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu8', json=registrarUsuarioJson)
		#Se crea el archivo
		salida = requests.post('http://localhost:8000/usuarios/usu8/archivos', json=archivoJson)
		#Se elimina el archivo
		salida = requests.delete('http://localhost:8000/usuarios/usu8/archivos', json= eliminarArchivoJson)
		#Se obtiene el archivo de la papelera
		salida = requests.get('http://localhost:8000/usuarios/usu8/papelera')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("usu8", salidaJson["Datos"][0]["Propietario"])
		self.assertEqual("hola", salidaJson["Datos"][0]["Nombre"])

	def test_09AlCompartirUnArchivoConOtroUsuarioEsteDebeTenerlo(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu9','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		#Datos necesarios para compartir archivo
		archivoCompartirJson = {'Propietario': 'usu9','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin', 'Usuarios': ['usu9_2'] }
		#Registro de dos usuarios
		salida = requests.post('http://localhost:8000/usuarios/usu9', json=registrarUsuarioJson)
		salida = requests.post('http://localhost:8000/usuarios/usu9_2', json=registrarUsuarioJson)
		#Se crea el archivo
		salida = requests.post('http://localhost:8000/usuarios/usu9/archivos', json=archivoJson)
		#Se comparte el archivo al segundo usuario
		salida = requests.put('http://localhost:8000/usuarios/usu9/archivos/compartir', json= archivoCompartirJson)
		#Se obtiene el archivo compartido del segundo usuario
		salida = requests.get('http://localhost:8000/usuarios/usu9_2/archivos')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("usu9", salidaJson["Datos"][0]["Propietario"])
		self.assertEqual("hola", salidaJson["Datos"][0]["Nombre"])

	def test_10BuscarArchivoPorEtiquetas(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu10','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		#Registro al usuario
		salida = requests.post('http://localhost:8000/usuarios/usu10', json=registrarUsuarioJson)
		#Se crea el archivo
		salida = requests.post('http://localhost:8000/usuarios/usu10/archivos', json=archivoJson)
		#Se busca el archivo por etiqueta
		salida = requests.get('http://localhost:8000/usuarios/usu10/archivos/etiquetas/saludo')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("usu10", salidaJson["Datos"][0]["Propietario"])
		self.assertEqual("hola", salidaJson["Datos"][0]["Nombre"])

	def test_11BuscarArchivoPorNombre(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu11','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		salida = requests.post('http://localhost:8000/usuarios/usu11', json=registrarUsuarioJson)
		salida = requests.post('http://localhost:8000/usuarios/usu11/archivos', json=archivoJson)
		#Se busca el archivo por nombre
		salida = requests.get('http://localhost:8000/usuarios/usu11/archivos/nombre/hola')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("usu11", salidaJson["Datos"][0]["Propietario"])
		self.assertEqual("hola", salidaJson["Datos"][0]["Nombre"])

	def test_12BuscarArchivoPorPropietario(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu12','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		salida = requests.post('http://localhost:8000/usuarios/usu12', json=registrarUsuarioJson)
		salida = requests.post('http://localhost:8000/usuarios/usu12/archivos', json=archivoJson)
		#Se busca el archivo por propietario
		salida = requests.get('http://localhost:8000/usuarios/usu12/archivos/propietario/usu12')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("usu12", salidaJson["Datos"][0]["Propietario"])
		self.assertEqual("hola", salidaJson["Datos"][0]["Nombre"])

	def test_13BuscarArchivoPorExtension(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu13','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		salida = requests.post('http://localhost:8000/usuarios/usu13', json=registrarUsuarioJson)
		salida = requests.post('http://localhost:8000/usuarios/usu13/archivos', json=archivoJson)
		#Se busca el archivo por extension
		salida = requests.get('http://localhost:8000/usuarios/usu13/archivos/extension/txt')
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("usu13", salidaJson["Datos"][0]["Propietario"])
		self.assertEqual("hola", salidaJson["Datos"][0]["Nombre"])

	def test_14ActualizarArchivo(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu14','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		#Datos del Archivo a actualizar
		actualizacionArchivoJson = {'Propietario': 'usu14', 'DirectorioOriginal' : 'documentos/bin', 'NombreOriginal': 'hola', 'ExtensionOriginal': 'txt','DirectorioNuevo': 'doc/','NombreNuevo': 'saludo', 'ExtensionNueva': 'bat','Etiquetas': ['hola','saludo'] }	
		#Se registra el usuario	
		salida = requests.post('http://localhost:8000/usuarios/usu14', json=registrarUsuarioJson)
		salida = requests.post('http://localhost:8000/usuarios/usu14/archivos', json=archivoJson)
		#Se actualiza el archivo
		salida = requests.put('http://localhost:8000/usuarios/usu14/archivos/actualizar',json= actualizacionArchivoJson)
		#Obtengo el archivo actualizado
		archivoActualizado = requests.get('http://localhost:8000/usuarios/usu14/archivos')
		archivoActualizadoJson = archivoActualizado.json()
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		#Verifico que se actualizo el nombre
		self.assertEqual("saludo", archivoActualizadoJson["Datos"][0]["Nombre"])

	def test_15RestaurarArchivo(self):
		#Datos del usuario
		MetaDatos = {'Email': 'pepe@mail.com','Foto': 'miFoto','Nombre': 'carlos','UltimaUbicacion': 'Bs As'}
		registrarUsuarioJson = {'Clave': 'MiClave','Cuota': '100500','MetaDatos': MetaDatos }
		#Datos del Archivo
		archivoJson = {'Propietario': 'usu15','Nombre': 'hola','Extension': 'txt','Directorio': 'documentos/bin','Etiquetas': ['hola','saludo'] }
		#Datos del Archivo a actualizar
		actualizacionArchivoJson = {'Propietario': 'usu15', 'DirectorioOriginal' : 'documentos/bin', 'NombreOriginal': 'hola', 'ExtensionOriginal': 'txt','DirectorioNuevo': 'doc/','NombreNuevo': 'saludo', 'ExtensionNueva': 'bat','FechaDeModificacion' : '2015/08/03','UsuarioQueModifico' : 'pepe300','Etiquetas': ['hola','saludo'] }
		#Datos del archivo a restaurar
		archivoRestaurarJson = 	{'Propietario': 'usu15','Nombre': 'saludo','Extension': 'bat','Directorio': 'doc/','FechaDeModificacion' : '2015/08/03','UsuarioQueModifico' : 'usu15' }
		#Se registra el usuario
		salida = requests.post('http://localhost:8000/usuarios/usu15', json=registrarUsuarioJson)
		salida = requests.post('http://localhost:8000/usuarios/usu15/archivos', json=archivoJson)
		#Se actualiza el archivo
		salida = requests.put('http://localhost:8000/usuarios/usu15/archivos/actualizar',json= actualizacionArchivoJson)
		#Se restaura el archivo
		salida = requests.put('http://localhost:8000/usuarios/usu15/archivos/restaurar',json= archivoRestaurarJson)
		#Obtengo el archivo restaurado
		archivoRestaurado = requests.get('http://localhost:8000/usuarios/usu15/archivos')
		archivoRestauradoJson = archivoRestaurado.json()
		salidaJson = salida.json()
		self.assertEqual("OK", salidaJson["Estado"])
		self.assertEqual("Archivo restaurado", salidaJson["Mensaje"])
		#Verifico que se actualizo el nombre
		self.assertEqual("hola", archivoRestauradoJson["Datos"][0]["Nombre"])



if __name__ == '__main__':

    unittest.main()
