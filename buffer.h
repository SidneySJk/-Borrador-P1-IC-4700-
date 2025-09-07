#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFFER_H
#define BUFFER_H

// Lee la cadena caracter por caracter para determinar su espacio de memoria
char* espacioDeMemoria(char* cadena) {
    
    //char* capacidad = NULL;
    int caracteres = 0;

    while (cadena[caracteres] != '\n' && cadena[caracteres] != '\0') {
        caracteres+=1;
    }
    char* capacidad = (char*)malloc((caracteres+1) * sizeof(char));
    if (capacidad == NULL) {
        printf("Error en la asignacion de memoria\n");
        //free(capacidad);
        exit(1);
    }

    strncpy(capacidad, cadena, caracteres);
    capacidad[caracteres] = '\0';
    return capacidad;
}

#endif