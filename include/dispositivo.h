#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include "kernel.h" // Para acceder a la estructura del proceso

void manejar_e_s(proceso *p, int *fila_actual); // Maneja la operación de E/S
void inicializar_dispositivo(); // Inicializa el dispositivo simulado

#endif

