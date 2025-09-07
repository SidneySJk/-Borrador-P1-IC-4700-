#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFFER_H
#define BUFFER_H

// Lee la cadena caracter por caracter para determinar su espacio de memoria
char* espacioDeMemoria() {
    
    char* cadena = NULL;
    int caracteres = 0;
    int c;
    c = getchar();

    while (( c = getchar()) != '\n' && c != EOF) {
        char *capacidad = realloc(cadena,( caracteres+2) * sizeof(char));//Se suma 2 para que quepa el caracter y '/0'
        if (capacidad == NULL) {
            printf("Error en la asignacion de memoria\n");
            free(capacidad);
            exit(1);
        }
        cadena = capacidad;
        cadena[caracteres] = (char)c;//'\0'
        caracteres+=1;
    }
    //char* capacidad = (char*)malloc((caracteres+1) * sizeof(char));

    //strncpy(capacidad, cadena, caracteres);
    if (cadena != NULL) {
        cadena[caracteres] = '\0';
    }
    //capacidad[caracteres] = '\0';

    //return capacidad;
    return cadena;
}

#endif