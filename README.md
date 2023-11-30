# Tareas_TC1031

## Tarea BST
En el archivo bst.h, la función visit() presentaba dos errores:

3.- esperada [10 8 12 110 18 112]
[8 10 12 18 110 112]
[8 18 112 110 12 10]
[10 8 12 110 18 112]
 programa [10 8 12 110 18 112]
[ 8 10 12 18 110 112]
[ 8 18 112 110 12 10]
fail

- Imprime un espacio antes del primer número (Ejemplo: [ 8 10 12 18 110 112]
  Este error se solucionó cambiando el lugar en la función en 

- No imprime la última opción del visit, es decir, el levelbylevel
  Para este error, implementé la función levelByLevel usando un stack. El código quita al nodo más reciente en el stack y, posteriormente, va agregando los hijos iquierdos y luego derechos que tiene un nodo. DE esta forma, comienza a imprimir de debajo hacia arriba por nivel.

3.- esperada [10 8 12 110 18 112]
[8 10 12 18 110 112]
[8 18 112 110 12 10]
[10 8 12 110 18 112]
 programa [10 8 12 110 18 112]
[8 10 12 18 110 112]
[8 18 112 110 12 10]
[10 8 12 110 18 112]
success

El resultado final ahora coincide con el del programa.
