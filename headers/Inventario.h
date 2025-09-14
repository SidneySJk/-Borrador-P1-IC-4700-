#ifndef INVENTARIO_H
#define INVENTARIO_H
#include <stdio.h>
#include <stdlib.h>
//#include "Inventario.c"

typedef struct {
    char *codigoBuscado;
    int *modificar;
 
} Inventario;

Inventario CrearInventario();
void leerTxt(Inventario *inve);
void actualizarCarga(Inventario *inve);//(char *codigoBuscado, int *modificar);
void LiberarMemoriaInventario(Inventario *inve);

#endif
