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
*check_user_name
*---------------
*Función para verificar que el cliente no este usando un nombre de usuario ya registrado previamente 
*ira de caracter en caracter dentro del fichero de usuarios hasta encontrar un ';'
*una vez allí comparara lo que ha leido vs el nombre de usuario que ha proporcionado el cliente
*en caso de ser iguales retornara un 1, en caso contrario continuara leyendo caracteres
*
*Argumentos:
*user_name: Nombre de usuario proporcionado por el cliente como tentativa para nombre de usuario
*MAX_SIZE: Longitud maxima de la cadena que extraere del archivo
*file_pointer: puntero al archivo donde guardare los nombres de los clientes registrados
*
*Retorna:
*1: en caso de que el nombre de usuario ya se encuentre registrado
*0: en caso de que no se encuentre registrado
*/

int check_user_name(char user_name[], size_t MAX_SIZE, FILE *file_pointer){
    char actual_string[MAX_SIZE];
    int c, comparison_result;
    int i = 0;
    while((c = getc(file_pointer)) != EOF){
        if(c == ';' || c == '\n'){
            actual_string[i] = '\0';
            comparison_result = compare_strings(actual_string, user_name, 100);
            if(comparison_result == 1){
                return 1;
            }
            i = 0;
        }
        else{
            actual_string[i] = c;    
            i++;
        }
    }
    return 0;    
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
    /*
    get_arguments(server_port, argv[1], 5);
    get_arguments(server_ipv4, argv[2], 20);
    add_client(server_port, server_ipv4, server_ipv6, &stack);
    add_client("8080","172.16.48.2", "db8:acad:1::2", &stack);
    add_client("8080","172.16.48.3", "db8:acad:1::3", &stack);
    show_list(stack);
    */
    int result;
    FILE *file_pointer = fopen("testing_file.txt", "a+");
    result = check_user_name("David\0", MAX_SIZE, file_pointer);
    rewind(file_pointer);
    if(result == 1){
        printf("\nEl nombre de usuario David ya esta ocupado");
    }else{
        printf("\nEsta disponible");
    }
    result = check_user_name("Daniel\0", MAX_SIZE, file_pointer);
    rewind(file_pointer);
    if(result == 1){
        printf("\nEl nombre de usuario Daniel ya esta ocupado");
    }else{
        printf("\nEsta disponible");
    }
    result = check_user_name("Santiago\0", MAX_SIZE, file_pointer);
    rewind(file_pointer);
    if(result == 1){
        printf("\nEl nombre de usuario Santiago ya esta ocupado");
    }else{
        printf("\nEsta disponible");
    }
    result = check_user_name("Santi\0", MAX_SIZE, file_pointer);
    rewind(file_pointer);
    if(result == 1){
        printf("\nEl nombre de usuario Santi ya esta ocupado");
    }else{
        printf("\nEsta disponible");
    }
    result = check_user_name("Cristian\0", MAX_SIZE, file_pointer);
    rewind(file_pointer);
    if(result == 1){
        printf("\nEl nombre de usuario Cristian ya esta ocupado");
    }else{
        printf("\nEsta disponible");
    }
    fclose(file_pointer);
}