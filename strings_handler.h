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