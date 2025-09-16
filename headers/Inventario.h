#ifndef INVENTARIO_H
#define INVENTARIO_H
#include <stdio.h>
#include <stdlib.h>
//#include "Inventario.c"

#define ARCHIVO_INVENTARIO "..data/Modificaciones.txt"
#define MAX_CARACTERES 110

typedef struct {
    char *codigoBuscado;
    int *modificar;
 
} Inventario;

Inventario CrearInventario();
void leerTxt(Inventario *inve);
void actualizarCarga(Inventario *inve);//(char *codigoBuscado, int *modificar);
void LiberarMemoriaInventario(Inventario *inve);
void iniciarActualizacionDeStock();
int modificarStock(int stock, Inventario *inve);

#endif