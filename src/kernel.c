#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "memoria.h" // Para la memoria
#include "dispositivo.h"
#include "kernel.h"
#include "archivo.h"


proceso tabla_procesos[MAX_PROCESOS] = {
    {1, 2, 5, 5, "listo", false},
    {2, 1, 6, 6, "listo", true},
    {3, 3, 4, 4, "listo", false}
};

//Ordenamos los procesos por prioridad
void ordenar_por_prioridad(proceso *tabla, int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        for (int j = i + 1; j < tamano; j++) {
            if (tabla[j].prioridad < tabla[i].prioridad) {
                proceso temporal = tabla[i];
                tabla[i] = tabla[j];
                tabla[j] = temporal;
            }
        }
    }
}
// NO PODEMOS USAR SPRINTF TENEMOS QUE HACERLO A LA ANTIGUA
/*
void mostrar_detalles() {
    char *memoria_video = (char *)0xB8000;
    int offset = 0;

    for (int i = 0; i < MAX_PROCESOS; i++) {
        const char *estado_actual = tabla_procesos[i].estado;
        offset += sprintf(memoria_video + offset * 2,
            "ID: %d, Prioridad: %d, Estado: %s, Restante: %d\n",
            tabla_procesos[i].id, tabla_procesos[i].prioridad,
            estado_actual, tabla_procesos[i].tiempo_restante);
    }
}
*/


int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void mostrar_detalles(int fila_actual, int id, const char *estado, int tiempo_restante) {
    char *memoria_video = (char *)0xB8000;
    int offset = fila_actual * 160;

    memoria_video[offset++] = 'P';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = '0' + id;
    memoria_video[offset++] = 0x0F;

    memoria_video[offset++] = ' ';
    memoria_video[offset++] = 0x0F;
    for (int i = 0; estado[i] != '\0'; i++) {
        memoria_video[offset++] = estado[i];
        memoria_video[offset++] = 0x0F;
    }

    memoria_video[offset++] = ' ';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = 'T';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = ':';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = '0' +  tiempo_restante;
    memoria_video[offset++] = 0x0F;
}
        

void pausa_simulada(int tiempo) {
    for (int i = 0; i < tiempo; i++) {
        for (volatile int j = 0; j < 100000; j++) {
            __asm__ __volatile__("nop");
        }
    }
}

void planificador() {
    inicializar_memoria();
    inicializar_dispositivo();
    mostrar_memoria();
    pausa_simulada(10000);
    ordenar_por_prioridad(tabla_procesos, MAX_PROCESOS);
    bool todos_terminados = false;
    int fila_actual = 1; // Comenzamos en la segunda línea (fila 1)

    while (!todos_terminados) {
        todos_terminados = true;

        for (int i = 0; i < MAX_PROCESOS; i++){
            if (tabla_procesos[i].tiempo_restante > 0) {
		todos_terminados = false;
                __builtin_memcpy(tabla_procesos[i].estado, "Ejecutando", 11);
                mostrar_detalles(fila_actual++, tabla_procesos[i].id, tabla_procesos[i].estado, tabla_procesos[i].tiempo_restante);
                asignar_memoria(tabla_procesos[i].id);
                if (tabla_procesos[i].necesita_e_s) {
                 manejar_e_s(&tabla_procesos[i], &fila_actual);
                }
		mostrar_memoria();
		int tiempo_ejecutado = (tabla_procesos[i].tiempo_restante > QUANTUM) ? QUANTUM : tabla_procesos[i].tiempo_restante;
		tabla_procesos[i].tiempo_restante -= tiempo_ejecutado;
		//mostrar_memoria();
		pausa_simulada(10000);

                if (tabla_procesos[i].tiempo_restante == 0) {
                    __builtin_memcpy(tabla_procesos[i].estado, "Terminado ", 11);
		    liberar_memoria(tabla_procesos[i].id);
                } else {
                    __builtin_memcpy(tabla_procesos[i].estado, "Listo     ", 11);
                }

		mostrar_detalles(fila_actual++, tabla_procesos[i].id, tabla_procesos[i].estado, tabla_procesos[i].tiempo_restante);
		mostrar_memoria();
            }
        }
    }
}

void mostrar_mensaje(const char *mensaje) {
    static int fila = 2; // Comenzar en la línea 20
    char *memoria_video = (char *)0xB8000;
    int offset = fila * 160;

    for (int i = 0; mensaje[i] != '\0'; i++) {
        memoria_video[offset++] = mensaje[i];
        memoria_video[offset++] = 0x0F; // Color blanco sobre negro
    }

    fila++; // Avanzar a la siguiente línea
    if (fila > 24) { // Si llegamos al final de la pantalla, volvemos a la línea 20
        fila = 2;
    }
}


void kernel_main(void) {
    //planificador();
    inicializar_archivos(); //Descomentar para funcionar la simulación de archivos
    simular_archivos();     // Descomentar para simular los archivos
    char *memoria_video = (char *)0xB8000;
    const char *mensaje = "Simulacion terminada";
    for (int i = 0; mensaje[i] != '\0'; i++) {
        memoria_video[i * 2] = mensaje[i];
        memoria_video[i * 2 + 1] = 0x0F;
    }

    while (1);
}

void simular_archivos() {
    crear_archivo("mod.txt", "Este es el Contenido de mod.txt");
    pausa_simulada(5000);
    crear_archivo("local.c", "Este es el Contenido de local.c");
    pausa_simulada(5000);
    listar_archivos();
    pausa_simulada(5000);
    leer_archivo("mod.txt");
    pausa_simulada(5000);
    eliminar_archivo("mod.txt");
    pausa_simulada(5000);
    listar_archivos();
    pausa_simulada(5000);
    crear_archivo("hola.java", "Contenido de hola.java");
    pausa_simulada(5000);
    listar_archivos();
}
