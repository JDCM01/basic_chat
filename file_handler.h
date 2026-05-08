#include<stdio.h>

/*login
*------
*Función para comparar una contraseña que entregue el usuario con la que se
*halle en el archivo, se llamara a la función check_string, si la 
*contraseña se encuentra en el archivo la función retornara un 1 y
*se le consedera acceso al usuario al chat
*si se equivoca mas de 3 veces en digitar la contraseña se le denegara el acceso
*
*Argumentos:
*-password: contraseña proporcionada por el cliente
*-file_pointer: Apuntador al archivo users.txt donde se encuentran los usuarios y las contraseñas
*
*Retorno:
*0: Si se deniega el acceso
*1: Si se concede el acceso
*/
int login(FILE *file_pointer){
    int i = 0;
    char password[100];
    while(i <= 3){
        printf("\nPara poder continuar debera digitar su contraseña: ");
        get_string(password, 100);
        if(check_string(password, 100, file_pointer, 1) == 1){ 
            return 1;
        }
        printf("\nContraseña incorrecta\n");    
        i++;
    }
    return 0;
}

/*
*register_user
*-------------
*Función para registrar un nombre de usuario en el archivo users.txt
*se le pide una contraseña al usuario para posteriormente insertar al nuevo
*usuario en users.txt  
*
*Argumentos:
*user_name: nombre del usuario a registrar
*file_pointer: apuntador al archivo users.txt  
*/
void register_user(char user_name[], FILE *file_pointer){
    char password[100];
    char string_to_insert[100];
    copy_string(user_name, string_to_insert, 100);
    printf("\n%s bienvenido al chat para poder registrarse debera digitar una contraseña: ", string_to_insert);
    get_string(password, 100);//Antes de entregar el chat hay que hacer fuciones para encriptar y desencriptar la contraseña
    insert_into_file(file_pointer, "\n", 100);
    concatenate_string(string_to_insert, ";\0");
    concatenate_string(string_to_insert, password);
    concatenate_string(string_to_insert, ";\0");
    concatenate_string(string_to_insert, "\n\0");
    insert_into_file(file_pointer, string_to_insert, 100);
}


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
}

