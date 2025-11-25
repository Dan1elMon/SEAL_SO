#include "archivo.h"
#include <stddef.h>
#include <stdbool.h>
#include "kernel.h"

static archivo lista_archivos[MAX_ARCHIVOS];
static int total_archivos = 0;

// Inicializa la lista de archivos
void inicializar_archivos() {
    total_archivos = 0;
    for (int i = 0; i < MAX_ARCHIVOS; i++) {
        lista_archivos[i].nombre[0] = '\0';
    }
}
// Función personalizada para concatenar dos cadenas
void mi_strcat(char *destino, const char *origen) {
    // Avanzar al final de la cadena destino
    while (*destino != '\0') {
        destino++;
    }

    // Copiar la cadena origen al final de destino
    while (*origen != '\0') {
        *destino = *origen;
        destino++;
        origen++;
    }

    // Agregar el carácter nulo al final
    *destino = '\0';
}

// Crea un archivo con nombre y contenido
void crear_archivo(const char *nombre, const char *contenido) {
    if (total_archivos >= MAX_ARCHIVOS) {
        mostrar_mensaje("gamaOS> ERROR: Límite de archivos alcanzado.");
        return;
    }

     char mensaje[50] = "gamaOS> create "; // Cadena base
    mi_strcat(mensaje, nombre);          // Usar la función personalizada
    mostrar_mensaje(mensaje);

    for (int i = 0; i < total_archivos; i++) {
        if (strcmp(lista_archivos[i].nombre, nombre) == 0) {
            mostrar_mensaje("gamaOS> ERROR: El archivo ya existe.");
            return;
        }
    }

    archivo nuevo;
    int i = 0;
    for (; nombre[i] != '\0' && i < TAM_NOMBRE - 1; i++) {
        nuevo.nombre[i] = nombre[i];
    }
    nuevo.nombre[i] = '\0';

    int j = 0;
    for (; contenido[j] != '\0' && j < TAM_CONTENIDO - 1; j++) {
        nuevo.contenido[j] = contenido[j];
    }
    nuevo.contenido[j] = '\0';

    nuevo.tamano = j;
    lista_archivos[total_archivos++] = nuevo;
    mostrar_mensaje("gamaOS> Archivo creado exitosamente.");
}

// Lista los archivos existentes
void listar_archivos() {
    mostrar_mensaje("gamaOS> list");
    if (total_archivos == 0) {
        mostrar_mensaje("gamaOS> No hay archivos.");
        return;
    }

    mostrar_mensaje("Lista de archivos:");
    for (int i = 0; i < total_archivos; i++) {
        mostrar_mensaje(lista_archivos[i].nombre);
    }
}

// Lee el contenido de un archivo por su nombre
void leer_archivo(const char *nombre) {
     char mensaje[50] = "gamaOS> read "; // Cadena base
    mi_strcat(mensaje, nombre);          // Usar la función personalizada
    mostrar_mensaje(mensaje);
    for (int i = 0; i < total_archivos; i++) {
        if (strcmp(lista_archivos[i].nombre, nombre) == 0) {
            mostrar_mensaje(lista_archivos[i].contenido);
            return;
        }
    }
    mostrar_mensaje("gamaOS> ERROR: Archivo no encontrado.");
}

// Elimina un archivo por su nombre
void eliminar_archivo(const char *nombre) {
     char mensaje[50] = "gamaOS> delete "; // Cadena base
    mi_strcat(mensaje, nombre);          // Usar la función personalizada
    mostrar_mensaje(mensaje);
    for (int i = 0; i < total_archivos; i++) {
        if (strcmp(lista_archivos[i].nombre, nombre) == 0) {
            for (int j = i; j < total_archivos - 1; j++) {
                lista_archivos[j] = lista_archivos[j + 1];
            }
            total_archivos--;
            mostrar_mensaje("Eliminado Correctamente!");
            return;
        }
    }
	    mostrar_mensaje("gamaOS> ERROR: Archivo no encontrado.");
}

