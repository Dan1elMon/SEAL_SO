#include "dispositivo.h"
#include "kernel.h" 

// Simula un dispositivo
static bool dispositivo_ocupado = false;

void inicializar_dispositivo() {
    dispositivo_ocupado = false; // Al inicio, el dispositivo está libre
}

void manejar_e_s(proceso *p, int *fila_actual) {
    if (p->necesita_e_s) {
        // Cambiar el estado a "En espera"
        __builtin_memcpy(p->estado, "en Espera ", 11);
        mostrar_detalles((*fila_actual)++, p->id, p->estado, p->tiempo_restante);

        // Simular tiempo de espera (E/S)
        pausa_simulada(100000);

        // Completar la operación de E/S
        p->necesita_e_s = false;
        __builtin_memcpy(p->estado, "Listo     ", 11);
    }
}

