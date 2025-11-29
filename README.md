# Proyecto Final - gamaOS - Sistemas Operativos

### Inconveniente Actual

- Se esta utilizando actualmente QEMU (Por su gran capacidad comparado a VirtualBox)
- En una primera instancia se logro, imprimir (en Qemu) letras en consola, usando un archivo bootloader.asm el cual resulto de forma satisfactoria-
- Como segunda parte se planeo hacer nuestro kernel (kernel.c) donde ira por ahora la logica del schedule, que en este caso sera el Round Robin (Prueba)
- LOS PROBLEMA ocurren cuando tratamos de ejecutarlo para que se muestra en QEMU, el cual no imprime nada.
- Se intento añadirle el bootloader.asm a la compilacion con Kernel.c, a pesar de eso QEMU solo imprime solo lo implementado en el bootloader.asm, QEMU ignora a kernel.c
- Se hara mas investigaciones para resolver el problema

### Solución problemas con Compilador Cruzado y QEMU
- Para seguir el tutorial "Bare Bones" de devOS WIKI se encontraron diferentes probleamas el cual se solucionaron como se indica abajo:
- Se soluciono el problema a la hora de implementar el compilador cruzado i386
- Se soluciono el problema del multiboot a la hora de cargar la imagen iso a qemu, debido a que qemu no reconocia la ISO generda


### Prueba con Python
- Debido al inconveniente anterior, se probara avanzar con python
- Posteriormente deberiamos acoplar qemu de ser posible
- ACTUALIZADO: Se cancela las pruebas en Python debido a que el se arreglaron los problemas con QEMU


