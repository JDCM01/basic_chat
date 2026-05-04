#include<stdio.h>
/*
*copy_string
*-----------
*funcion para copiar los elementos de una string en otra
*
*argumentos:
*-from_this: string que se debe copiar
*-to_this: lugar donde alojare la copia
*-length: ultima posicion del array
**/
void copy_string(char from_this[], char to_this[], int length){
    int i = 0;
    while(i < length){
        to_this[i] = from_this[i];    
        i++;
    }
}

/*
*concatenate_string
*------------------
*Función para agregar mas caracteres al final de una string
*va a recorrer la string hasta que encuentre '\0' o caracter nulo
*que es donde termina la  string y lo reemplazara con el primer caracter
*de la cadena que se agregara, se ira copiando caracter a caracter hasta que 
*se encuentre '\0'
*
*argumentos:
*-this_string: string base
*-plus_this: string que se agregara al final de this_string
*/
void concatenate_string(char this_string[], char plus_this[]){
    int i = 0;
    int j = 0;
    while(this_string[i] != '\0'){    
        i++;
    }
    while(plus_this[j] != '\0'){
        this_string[i] = plus_this[j];
        j++;
        i++;
    }
    this_string[i] = '\0';
}

/*
* create_message
* --------------
* Lee una línea de entrada desde el teclado usando getchar() y la almacena
* en el arreglo 'string'.
*
* La lectura se detiene cuando ocurre alguno de los siguientes casos:
* - Se alcanza el fin de archivo (EOF)
* - Se encuentra un salto de línea ('\n')
* - Se alcanza la longitud máxima permitida (max_length - 1)
*
* Al finalizar, se agrega el carácter nulo ('\0') para indicar el final
* de la cadena.
*
* Parámetros:
* - message: arreglo donde se almacenará la cadena
* - max_length: tamaño máximo del arreglo
*/
void create_message(char message[], size_t max_length){
    int character;
    int i = 0;
    while(i< max_length - 1 && (character=getchar()) != EOF && character != '\n'){
        message[i] = character;
        i++;
    }
    message[i] = '\0';
}

/*
*get_arguments
*-------------
*
*Esta funcion recorrera un arreglo de caracteres volcando cada uno de 
*los caracteres de argv en string hasta que se de una de las posibles
*condiciones de parada:
*-i alcance la penultima posicion del arreglo sobre el cual estoy volcando la informacion
*-la posicion i del arreglo argv sea EOF indicando un error o final del archivo
*
*
*argumentos:
*-string_length: longitud maxima o ultima posicion de la string en la cual estoy volcando la informacion
*-argv: array de uno de los argumentos pasados por consola
*/
void get_arguments(char string[], char argv[], size_t string_length){
    int i = 0;
    int c;
    while(i < string_length - 1 && argv[i] != EOF){//&& (argv += i) != EOF
        string[i] = argv[i];
        i++;
    }
    string[i] = '\0';
}