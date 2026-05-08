#include<stdio.h>
/*
*check_string
*---------------
*Función para verificar que el cliente no este usando un nombre de usuario ya registrado previamente 
*ira de caracter en caracter dentro del fichero de usuarios hasta encontrar un ';'
*una vez allí comparara lo que ha leido vs la cadena que ha proporcionado el cliente
*en caso de ser iguales retornara un 1, en caso contrario continuara leyendo caracteres
*
*Argumentos:
*string_to_validate: Nombre de usuario o contraseña proporcionado por el cliente 
*MAX_SIZE: Longitud maxima de la cadena que se extraera del archivo
*file_pointer: puntero al archivo donde se guardaran los nombres de los clientes registrados
*option: Para poder reusar la función se necesita saber si se comprobara contraseña o nombre de 
*usuario, por lo cual option indica si es 0 es es el nombre de usuario 
*y debe ir recorriendo todo el archivo
*si es 1 indica que se comprobara contraseña y solo debe ir hasta que encuentre salto de linea
*o EOF
*
*Retorna:
*1: en caso de que el nombre de usuario ya se encuentre registrado o la contraseña coincida
*0: en caso de que no se encuentre registrado
*/

int check_string(char string_to_validate[], size_t MAX_SIZE, FILE *file_pointer, int option){
    char actual_string[MAX_SIZE];
    int c, comparison_result;
    int i = 0;
    if(option == 0){
        while((c = getc(file_pointer)) != EOF){
            if(c == ';'){
                actual_string[i] = '\0';
                comparison_result = compare_strings(actual_string, string_to_validate, 100);
                if(comparison_result == 1){
                    return 1;
                }
                i = 0;
            }
            else{
                if(c != '\n'){
                    actual_string[i] = c;    
                    i++;
                }
                
            }
        }
        return 0;  
    }
    else{
        while((c = getc(file_pointer)) != EOF && c != ';'){
            if(c != '\n' && c != ';'){
                actual_string[i] = c;
                i++;
            }
            
        }
        actual_string[i] = '\0';
        comparison_result = compare_strings(actual_string, string_to_validate, 100);
        if(comparison_result == 1){
            return 1;
        }
        else{
            return 0;
        }  
    }
}


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
*from_int_to_char
*----------------
*Función para traducir de entero a caracter, segun la tabla ascii
*
*argumentos:
*character: caracter a traducir
*
*Retorno:
*un caracter que puede ir desde la a hasta z, punto, coma, dos puntos, 
*punto y coma, caracter nulo, salto,
*de linea
*/
char from_int_to_char(int character){
    int i;
    /*65-89 A-Z
    , = 44
    . = 46
    : = 58
    ; = 59
    \n = 10
    \0 = 0*/
    char *letters[] = {"a", "b", "c", "d", "f", "g", "h", "i", "j", 
                "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "\0"};
    if(character >= 65 && character <= 89){
        i = character - 65;
        return *letters[i];
    }else if(character == 44){
        return ',';
    }else if(character == 46){
        return '.';
    }else if(character == 58){
        return ':';
    }else if(character == 59){
        return ';';
    }else if(character == 10){
        return '\n';
    }else if(character == 0){
        return '\0';
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
*compare_strings
*---------------
*Función que comparara todos los caracteres de dos strings, y las recorrea hasta 
*que suceda una de las condiciones de parada:
*-el caracter actual analizado sea '\0' en alguna de las dos cadenas
*-algun caracter sea distinto 
*-se alcance la longitud máxima de las cadenas(MAX_SIZE)
*
*Argumentos:
*string_a: La primera de las dos strings
*string_b: La segunda de las dos strings
*MAX_SIZE: valor máximo que podra tener la cadena
*
*Retorna:
*1 si recorre ambas strings hasta encontrar '\0' en ambas cadenas
*0 en cualquier otro caso
*/
int compare_strings(char string_a[], char string_b[], size_t MAX_SIZE){
    int i = 0;
    while(i < MAX_SIZE && (string_a[i] != '\0') && (string_b[i] != '\0') ){
        if(string_a[i] != string_b[i]){
            return 0;
        }
        i++;
    }
    if((string_a[i] == string_b[i]) && (string_a[i] == '\0')){
        return 1;
    }else{
        return 0;
    }
}

/*
* get_string
* ----------
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
void get_string(char message[], size_t max_length){
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