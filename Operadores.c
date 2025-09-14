
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Lee la cadena caracter por caracter para determinar su espacio de memoria

char* espacioDeMemoria() {
    
    char* cadena = NULL;
    int caracteres = 0;
    int c;

    while (( c = getchar()) != '\n' && c != EOF) { //Fuente: https://rabbit.eng.miami.edu/class/een218/getchar.html
        char* capacidad = realloc(cadena,( caracteres+2) * sizeof(char));//Se suma 2 para que quepa el caracter y '/0'
        if (capacidad == NULL) {
            printf("Error en la asignacion de memoria\n");
            free(capacidad);
            exit(1);
        }
        cadena = capacidad;
        cadena[caracteres] = (char)c;//'\0'
        caracteres+=1;
    }
   
    if (cadena != NULL) {
        cadena[caracteres] = '\0';
    }
    //capacidad[caracteres] = '\0';

    //return capacidad;
    return cadena;
}
