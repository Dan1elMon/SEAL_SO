#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#define MAX_ARCHIVOS 10
#define TAM_NOMBRE 20
#define TAM_CONTENIDO 100

typedef struct {
    char nombre[TAM_NOMBRE];
    char contenido[TAM_CONTENIDO];
    int tamano;
} archivo;

void inicializar_archivos();
void crear_archivo(const char *nombre, const char *contenido);
void listar_archivos();
void leer_archivo(const char *nombre);
void eliminar_archivo(const char *nombre);

#endif

