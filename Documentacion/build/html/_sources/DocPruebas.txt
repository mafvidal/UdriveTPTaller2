.. _DocPruebas:

Documentación de pruebas
========================

Para probar el servidor se desarrollaron test con la librería `gtest <https://code.google.com/p/googlemock/>`_, para ello se programaron 11 tests unitarios, además se realizaron otros 16 tests unitarios con python requests, para probar el funcionamiento del servidor, simulando al cliente.

En todo el desarrollo del servidor, también se utilizo **Postman**, para verificar el envío de mensajes.

Con los tests realizados se realizaron pruebas métricas, obteniendo un code coverage del 77.7% en lineas de código, y 84.4% en funciones.

Para ver el code coverage, diríjase en la carpeta del proyecto a servidor/tests/cov, y abra el archivo index.html.

|
|
| :ref:`Volver a la pagina anterior <DocTecnica>`
| :ref:`Volver a la pagina principal <index>`
