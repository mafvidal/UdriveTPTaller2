.. _DocPruebas:

Documentación de pruebas
========================

Para probar el servidor se desarrollaron test con la librería `gtest <https://code.google.com/p/googlemock/>`_, para ello se programaron 11 tests unitarios, además se realizaron otros 16 tests unitarios con python requests, para probar el funcionamiento del servidor, simulando al cliente.

En todo el desarrollo del servidor, también se utilizo **Postman**, para verificar el envío de mensajes.

Con los tests realizados se realizaron pruebas métricas, obteniendo un code coverage del 77.7% en lineas de código, y 84.4% en funciones.

Para ver el code coverage, diríjase en la carpeta del proyecto a servidor/tests/cov, y abra el archivo index.html.

Finalmente se analizo si el servidor perdía o no memoria, por lo que se utilizo la herramienta **valgrind** para analizarlo, corriendo el servidor y utilizándolo de forma común, y se obtuvo el siguiente resultado:

.. code-block:: shell

	valgrind --leak-check=full ./servidor 
	==6453== Memcheck, a memory error detector
	==6453== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
	==6453== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
	==6453== Command: ./servidor
	==6453== 
	Ingrese q y presione enter para salir
	q
	==6453== 
	==6453== HEAP SUMMARY:
	==6453==     in use at exit: 0 bytes in 0 blocks
	==6453==   total heap usage: 12,438 allocs, 12,438 frees, 3,058,906 bytes allocated
	==6453== 
	==6453== All heap blocks were freed -- no leaks are possible
	==6453== 
	==6453== For counts of detected and suppressed errors, rerun with: -v
	==6453== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Por lo que se puede concluir, que el servidor no pierde memoria al ejecutarse.

|
|
| :ref:`Volver a la pagina anterior <DocTecnica>`
| :ref:`Volver a la pagina principal <index>`
