Mini Shell
=====
Tarea Nro. 2 de INF-295 Sistemas Operativos  
Profesor **Xavier Bonnaire**

El objetivo de la tarea es escribir un mini-shell en Linux, con la posibilidad de correr un programa en primer plano, o en segundo plano.


Ejecución
-------
Ejecutar makefile, luego  ``./shell``

Pruebas
-----
En el repositorio está ``delay_test.c``. Archivo que ayudará probar ejecución en segundo plano. 


Precaución
-------------
Dependiendo el programa a ejecutar en segundo plano, la consola hace salto de linea. Se corrige ingresando **``!x``**.


Supuestos
---------
* No reconoce ``chdir`` (cd).

Atajos
----------
* **!q, quit, exit, logout**: salir de la consola
* **!c, credits**: Créditos
* **!h, help**: muestra atajos en la consola
* **!x**: genera una nueva linea de ejecución