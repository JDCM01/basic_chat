#include<stdio.h>
#include<stdlib.h>
#include"strings_handler.h"
#include"list_handler.h"
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
    char server_port[port_size];
    char server_ipv4[ipv4_size];
    char server_ipv6[ipv6_size];
    get_arguments(server_port, argv[1], 5);
    get_arguments(server_ipv4, argv[2], 20);
    add_client(server_port, server_ipv4, server_ipv6, &stack);
    add_client("8080","172.16.48.2", "db8:acad:1::2", &stack);
    add_client("8080","172.16.48.3", "db8:acad:1::3", &stack);
    show_list(stack);
}