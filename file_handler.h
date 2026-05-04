#include<stdio.h>

/*
*print_from_file
*----------------
*esta funcion va recorrer el archivo hasta que se cumpla la condicion:
*-getc entregue EOF indicando un error o el final del archivo
*
*parametros:
*file_pointer: apuntador al archivo
*/
void print_from_file(FILE *file_pointer){
    int c;
    printf(" ");
    while((c = getc(file_pointer)) != EOF){
        printf("%c", c);
    }    
}

/*
*insert_into_file
*----------------
*esta funcion va a iterar poniendo caracteres en el archivo hasta que se cumpla una de las condiciones:
*-i alcance la ultima posicion del vector string
*-el caracter actual sea '\0' o caracter nulo
*-putc entregue EOF indicando un error o el final del archivo
*
*parametros:
*file_pointer: apuntador al archivo
*-string: vetor de caracteres a insertar en el archivo
*-max_length: tamaño maximo del vector
*/
void insert_into_file(FILE *file_pointer, const char string[], size_t max_length){
    int i = 0;
    while(i<max_length && string[i] != '\0' && (putc(string[i], file_pointer) != EOF)){
        i++;
    }
    putc(32, file_pointer);/*32 en el estandar ascii es el espacio en blanco*/
}


void create_file_pointer(FILE *file_pointer, const char file_name[]){
    file_pointer = fopen(file_name,"w+");//recordar hacer fclose(file_pointer cuando no lo este usando mas)
}