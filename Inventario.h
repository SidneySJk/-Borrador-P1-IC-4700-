#ifndef Inventario_H
#define Inventario_H

typedef struct {
    char *codigoBuscado;
    int *cantidadModificar;
 
} Inventario;

Inventario CrearInventario();
void leerTxt();
void actualizarCarga(char *codigoBuscado, int *cantidadModificar);

#endif