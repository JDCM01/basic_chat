#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include"list_handler.c"
#include"file_handler.c"
#include"strings_handler.c"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>



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

//size_t argc, char *argv[]
void main(){
    /*
    char port[5];
    char ipv4[20];
    get_arguments(port, argv[1], 5);
    get_arguments(ipv4, argv[2], 20);
    copy_string(port, port, 5);
    copy_string(ipv4, ipv4, 20);
    */
    /*
    *Creando el socket
    *AF_INET: Indica que se usara IPv4. Si se quiere llegara a usar IPv6, sería AF_INET6.
    *SOCK_STREAM: Indica que se llevara a cabo 
    *una conexión TCP. Para UDP se usa SOCK_DGRAM
    *0: Protocolo por defecto osea IP
    */
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    
    //Dandole identidad al cliente
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // la dirección a la que se debe conectar
    address.sin_port = htons(8080);       // El puerto (htons convierte al orden de bytes de red)

    //conectando al servidor
    if(connect(client_fd, (struct sockaddr *)&address, sizeof(address)) == -1){
        perror("Error al conectar con el servidor");
        exit(EXIT_FAILURE);
    }
    
    char incoming_message[MAX_SIZE];
    char access[MAX_SIZE];
    char user_name[NAMES_SIZE];
    char emissary[NAMES_SIZE];
    color_format("Server: Para poder unirse al chat digite el nombre de usuario que desea usar: \0", "\0");
    get_string(user_name);
    //Mandando nombre de usuario
    write(client_fd, user_name, string_length(user_name, NAMES_SIZE));
    //Mandando contraseña
    receive_and_send(client_fd, access, user_name, MAX_SIZE, NAMES_SIZE);
    //respuesta por parte del servidor acceso concedido denegado
    read(client_fd, incoming_message, sizeof(incoming_message));
    color_format(incoming_message, user_name);
    close(client_fd);
}