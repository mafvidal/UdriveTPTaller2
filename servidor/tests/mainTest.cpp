#include <iostream>
#include <list>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BaseDeDatos.h"
#include "Constantes.h"
#include <fstream>
#include "Usuario.h"
#include "Archivo.h"
#include "json/json.h"

using namespace std;

string cargarJsonArchivoEliminado(const string &propietario){

	Value datosArchivo;
	Reader reader;
	ifstream test("archivoEliminado.json", ifstream::binary);
	reader.parse( test, datosArchivo, false );
	datosArchivo["Propietario"] = propietario;

	return datosArchivo.toStyledString();

}

string cargarJsonArchivo(const string &propietario){

	Value datosArchivo;
	Reader reader;
	ifstream test("archivo.json", ifstream::binary);
	reader.parse( test, datosArchivo, false );
	datosArchivo["Propietario"] = propietario;

	return datosArchivo.toStyledString();

}

string cargarDatosUsuarioActualizado(){

	//Cargo el json de prueba
	Value datosUsuario;
	Reader reader;
	ifstream test("datosDeUsuarioActualizado.json", ifstream::binary);
	reader.parse( test, datosUsuario, false );

	return datosUsuario.toStyledString();

}

string cargarJsonUsuario(){

	//Cargo el json de prueba
	Value datosUsuario;
	Reader reader;
	ifstream test("datosDeUsuario.json", ifstream::binary);
	reader.parse( test, datosUsuario, false );

	return datosUsuario.toStyledString();

}

TEST(baseDeDatos, AlGuardarUnArchivoYRecuperarloDeboObtenerloCorrectamente) {
	
	BasedeDatos *base=BasedeDatos::obteberInstancia();

	base->guardar(USUARIOS,"usuarioTest1",cargarJsonUsuario());

	EXPECT_EQ(cargarJsonUsuario(),base->leer(USUARIOS,"usuarioTest1"));

}

TEST(baseDeDatos, AlGuardarYEliminarElDatoNoDebePermanecerEnLaBaseDeDatos) {
	
	BasedeDatos *base=BasedeDatos::obteberInstancia();

	base->guardar(USUARIOS,"usuarioTest2",cargarJsonUsuario());
	base->eliminar(USUARIOS,"usuarioTest2");

	EXPECT_EQ("",base->leer(USUARIOS,"usuarioTest2"));

}

TEST(baseDeDatos, SiElUsuarioNoExisteAlIdentificarmeDeboRecibirUnFalse) {
	
	Usuario usuario;

	Value identificarse;

	identificarse["Clave"] = "Mi_Clave";

	EXPECT_FALSE(usuario.identificarse("usuarioTest3",identificarse.toStyledString()));

}

TEST(baseDeDatos, SiElUsuarioExisteAlIdentificarmeDeboRecibirUnTrue) {
	
	Usuario usuario;

	Value identificarse;

	identificarse["Clave"] = "MiClave";

	usuario.registrarse("usuarioTest4",cargarJsonUsuario());

	EXPECT_TRUE(usuario.identificarse("usuarioTest4",identificarse.toStyledString()));

}

TEST(baseDeDatos, AlRegistrarUnUsuarioYObtenerSusDatosEstosDebenSerCorrectos) {
	
	Usuario usuario;

	Value identificarse;
	Value datos;
	Reader lector;

	identificarse["Clave"] = "MiClave";

	usuario.registrarse("usuarioTest5",cargarJsonUsuario());

	lector.parse(usuario.obtenerDatos("usuarioTest5"),datos,false);

	EXPECT_EQ("fulanitoMail@mail.com",datos.get("Email","").asString());
	EXPECT_EQ("FulanitoFoto",datos.get("Foto","").asString());
	EXPECT_EQ("Fulanito",datos.get("Nombre","").asString());
	EXPECT_EQ("Bs As",datos.get("UltimaUbicacion","").asString());

}

TEST(baseDeDatos, AlActualizarLosDatosDeUnUsuarioEstosDebenActualizarseCorrectamente) {

	Usuario usuario;
	Value datos;
	Reader lector;

	usuario.registrarse("usuarioTest6",cargarJsonUsuario());
	usuario.actualizarDatos("usuarioTest6",cargarDatosUsuarioActualizado());

	lector.parse(usuario.obtenerDatos("usuarioTest6"),datos,false);

	EXPECT_EQ("otroMail@mail.com",datos.get("Email","").asString());
	EXPECT_EQ("otraFoto",datos.get("Foto","").asString());
	EXPECT_EQ("Fulanito",datos.get("Nombre","").asString());
	EXPECT_EQ("Corrientes",datos.get("UltimaUbicacion","").asString());
}

TEST(baseDeDatos, AlAgregarUnArchivoElUsuarioDebeTenerlo) {

	Usuario usuario;
	Archivo archivo;
	Reader  lector;
	Value datosArchivo;

	usuario.registrarse("usuarioTest7",cargarJsonUsuario());
	//Primero verifico que no tenga archivos
	lector.parse(usuario.obtenerArchivos("usuarioTest7"),datosArchivo,false);

	EXPECT_EQ(0,datosArchivo.size());
	
	archivo.crearArchivo("usuarioTest7",cargarJsonArchivo("usuarioTest7"));

	lector.parse(usuario.obtenerArchivos("usuarioTest7"),datosArchivo,false);

	//El usuario debe tener el archivo
	EXPECT_EQ(1,datosArchivo.size());

}


TEST(baseDeDatos, alEliminarUnArchivoElUsuarioDebeTenerloEnlaPapelera) {

	Usuario usuario;
	Archivo archivo;
	Reader  lector;
	Value datosArchivo;

	usuario.registrarse("usuarioTest8",cargarJsonUsuario());

	//Primero verifico que no tenga archivos
	lector.parse(usuario.verPapelera("usuarioTest8"),datosArchivo,false);

	EXPECT_EQ(0,datosArchivo.size());
	
	archivo.crearArchivo("usuarioTest8",cargarJsonArchivo("usuarioTest8"));
	archivo.eliminarArchivo("usuarioTest8",cargarJsonArchivoEliminado("usuarioTest8"));

	lector.parse(usuario.verPapelera("usuarioTest8"),datosArchivo,false);

	//El usuario debe tener el archivo
	EXPECT_EQ(1,datosArchivo.size());

}

TEST(baseDeDatos, alCompartirUnArchivoConUnUsarioEsteDebeTenerlo) {

	Usuario usuario;
	Archivo archivo;
	Reader  lector;
	Value datosArchivo;	
	Value datosArchivo1;
	Value datosArchivo2;
	Value usuarios;

	usuarios.append("usuarioTest9_1");
	usuarios.append("usuarioTest9_2");

	usuario.registrarse("usuarioTest9",cargarJsonUsuario());
	usuario.registrarse("usuarioTest9_1",cargarJsonUsuario());
	usuario.registrarse("usuarioTest9_2",cargarJsonUsuario());

	//Primero verifico que no tenga archivos
	lector.parse(usuario.obtenerArchivos("usuarioTest9_1"),datosArchivo1,false);
	lector.parse(usuario.obtenerArchivos("usuarioTest9_2"),datosArchivo2,false);

	EXPECT_EQ(0,datosArchivo1.size());
	EXPECT_EQ(0,datosArchivo2.size());
	
	archivo.crearArchivo("usuarioTest9",cargarJsonArchivo("usuarioTest9"));

	archivo.compartir(usuarios.toStyledString(),cargarJsonArchivo("usuarioTest9"));

	lector.parse(usuario.obtenerArchivosCompartidos("usuarioTest9_1"),datosArchivo1,false);
	lector.parse(usuario.obtenerArchivosCompartidos("usuarioTest9_2"),datosArchivo2,false);

	//El usuario debe tener el archivo
	EXPECT_EQ(1,datosArchivo1.size());
	EXPECT_EQ(1,datosArchivo2.size());

}

TEST(baseDeDatos, alEliminarUnArchivoYRecuperarloElUsuarioDebeTenerlo) {

	Usuario usuario;
	Archivo archivo;
	Reader  lector;
	Value datosArchivo;

	usuario.registrarse("usuarioTest10",cargarJsonUsuario());

	archivo.crearArchivo("usuarioTest10",cargarJsonArchivo("usuarioTest10"));

	archivo.eliminarArchivo("usuarioTest10",cargarJsonArchivoEliminado("usuarioTest10"));

	//Primero verifico que no tenga el archivo eliminado
	lector.parse(usuario.obtenerArchivos("usuarioTest10"),datosArchivo,false);

	EXPECT_EQ(0,datosArchivo.size());

	//Recupero el archivo de la papelera
	archivo.recuperarArchivo("usuarioTest10",cargarJsonArchivo("usuarioTest10"));
	
	lector.parse(usuario.obtenerArchivos("usuarioTest10"),datosArchivo,false);

	//Verifico que vuelva a tener el archivo
	EXPECT_EQ(1,datosArchivo.size());

}

TEST(baseDeDatos, alEliminarUnArchivoCompartidoLosDemasUsuarioDebenTenerloEnLaPapelera) {

	Usuario usuario;
	Archivo archivo;
	Reader  lector;
	Value datosArchivo;	
	Value datosArchivo1;
	Value datosArchivo2;
	Value usuarios;

	usuarios.append("usuarioTest11_1");
	usuarios.append("usuarioTest11_2");

	usuario.registrarse("usuarioTest11",cargarJsonUsuario());
	usuario.registrarse("usuarioTest11_1",cargarJsonUsuario());
	usuario.registrarse("usuarioTest11_2",cargarJsonUsuario());

	//Primero verifico que no tenga archivos
	//lector.parse(usuario.obtenerArchivos("usuarioTest9_1"),datosArchivo1,false);
	//lector.parse(usuario.obtenerArchivos("usuarioTest9_2"),datosArchivo2,false);

	//EXPECT_EQ(0,datosArchivo1.size());
	//EXPECT_EQ(0,datosArchivo2.size());
	
	archivo.crearArchivo("usuarioTest11",cargarJsonArchivo("usuarioTest11"));

	archivo.compartir(usuarios.toStyledString(),cargarJsonArchivo("usuarioTest11"));

	archivo.eliminarArchivo("usuarioTest11",cargarJsonArchivoEliminado("usuarioTest11"));

	lector.parse(usuario.verPapelera("usuarioTest11_1"),datosArchivo1,false);
	lector.parse(usuario.verPapelera("usuarioTest11_2"),datosArchivo2,false);

	//El usuario debe tener el archivo en la papelera
	EXPECT_EQ(1,datosArchivo1.size());
	EXPECT_EQ(1,datosArchivo2.size());

}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
  	return RUN_ALL_TESTS();
}
