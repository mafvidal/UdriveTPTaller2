/*
 * Excepciones.h
 *
 *  Created on: 9 de nov. de 2015
 *      Author: mafv
 */

#ifndef EXCEPCIONES_H_
#define EXCEPCIONES_H_

/**
* Excepcion si el archivo no existe en la base de datos
*/
class EArchivoInexistente {};
/**
* Excepcion si se supera el limite de cuota
*/
class ELimiteDeCuota {};
/**
* Excepcion si se quiere eliminar un archivo ya eliminado
*/
class EArchivoYaEliminado {};
/**
* Excepcion si se quiere recuperar un archivo ya existente
*/
class EArchivoExistente {};
/**
* Excepcion si el usuario no existe en el sistema
*/
class EUsuarioInexistente {};

#endif /* EXCEPCIONES_H_ */
