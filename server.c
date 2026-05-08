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
    rewind(file_pointer);
    print_from_file(file_pointer);
    fclose(file_pointer);
    */

    /*Ejemplo de como usar el color_format
    char message[] = "David: Hola este es un mensaje de prueba\0";
    char piece[100];
    extract_from_string(message, piece, ':', 100);
    color_format(message, piece);
    char message2[] = "Server: Daniel se ha unido al chat";
    color_format(message2, piece);
    char message3[] = "Daniel: Hola David tu ejemplo esta muy interesante";
    color_format(message3, piece);
    */
}