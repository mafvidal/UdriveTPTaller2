.. _Troubleshooting:

Problemas comunes y solución
============================

* **No encuentro la carpeta build**

	La carpeta build la debe crear el usuario, salvo en docker, para ello ejecute **mkdir build**

* **Al querer compilar el servidor sale un mensaje de error:**

	* No rule to make target '../bibliotecas/rocksdb/librocksdb.a'

		Esto se debe a que no fue compilada la biblioteca RocksDB, para ello siga las siguiente :ref:`instrucciones <ConfigurarRocksdb>`

	* No rule to make target '../bibliotecas/gmock/gtest/libgtest.a'

		Esto se debe a que no fue compilada la biblioteca gmock/gtest, para ello siga las siguiente :ref:`instrucciones <ConfigurarTests>`

* **Al correr el servidor aparece el siguiente error**

	* Error al conectarse al puerto, Presione cualquier tecla y enter para salir

		Esto se debe a que otra aplicación esta utilizando el puerto 8000, que utiliza el servidor, como solución puede cerrar la aplicación que lo este utilizando, o modificar el puerto que utiliza el servidor, el cual se encuentra en el archivo /servidor/clasesCP2/constantes.h, y modifique el valor de la variable **s_http_port**.

	* Para cualquier otro tipo de error al ejecutar el servidor, puede ejecutarlo activando los diferentes niveles de log, y analizar el archivo log.txt.

|
|
| :ref:`Volver a la pagina anterior <ManAdministracion>`
| :ref:`Volver a la pagina principal <index>`
