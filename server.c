#include<stdio.h>
#include<stdlib.h>
#include"strings_handler.h"
#include"list_handler.h"
#include"file_handler.h"
/*#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>*/

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
*main
*----
*
*argumentos:
*-argc: cantidad de argumentos pasados por consola en el caso de este programa debe ser igual a 4
*-argv: array de argumentos pasados por consola, en el caso de este programa los argumentos
*pasados por consola seran puerto y direccion ipv4 y 6 aunque para pruebas sencillas se 
*ignorara el ipv6, la posicion 0 sera nombre del programa server.c la posicion 1 sera puerto 
*y la posicion 2 sera la direccion ip en caso de que se este manejando tambien direccion ipv6
*sera la posicion 3 del vector
*/

void main(size_t argc, char *argv[]){
    List* stack = NULL; 
    size_t MAX_SIZE = 100;
    char server_port[port_size];
    char server_ipv4[ipv4_size];
    char server_ipv6[ipv6_size];
    int result;
    FILE *file_pointer = fopen("users.txt", "a+");
    /*Ejemplo para darle acceso a alguien que ya se encuentra registrado
    result = check_string("David\0", MAX_SIZE, file_pointer, 0);
    
    if(result == 1){
        //printf("\nEl nombre de usuario David ya esta ocupado");
        if(login(file_pointer) == 1){
            printf("Bienvenido al chat");
        }
        else{
            printf("Acceso denegado");
        }
    }else{
        //printf("\nEsta disponible");
        register_user("David\0", file_pointer);
    }
    
    rewind(file_pointer);
    */
    rewind(file_pointer);
    print_from_file(file_pointer);
    fclose(file_pointer);
}