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

/*reading_arguments
*------------------
*componentes:
*-user_name: nombre del usuario
*-client_fd: descriptor de archivos del cliente*/
typedef struct reading_arguments{
    char user_name[NAMES_SIZE];
    int client_fd;
}reading_arguments;

/*reading_thread
*---------------
*Función que estara pidiendole al usuario mensajes constantemente 
*y enviandoselas al servidor
*
*argumentos:
*-user_name: nombre del cliente
*-client_fd: file descriptor del cliente*/
void* reading_thread(void* args){
    reading_arguments* arguments = (reading_arguments*)args;
    while(1){
        printf("\nMensaje: ");
        char message_to_send[MAX_SIZE];
        message_to_send[0] = '\0';
        char string[MAX_SIZE];
        concatenate_string(message_to_send, arguments->user_name, MAX_SIZE);//probablemente halla problemas aqui
        concatenate_string(message_to_send, ": \0", MAX_SIZE);
        get_string(string);
        concatenate_string(message_to_send, string, MAX_SIZE);
        write(arguments->client_fd, message_to_send, string_length(message_to_send, MAX_SIZE));
    }
}

/*listening_arguments
*--------------------
*componentes:
*client_fd: descriptor de archivos del cliente
*user_name: nombre del cliente*/
typedef struct listening_arguments{
    int client_fd;
    char user_name[NAMES_SIZE];
}listening_arguments;

/*listening_thread
*-----------------
*Función creada para estar constantemente revisando si le llega un mensaje al cliente 
*
*argumentos:
*client_fd: file descriptor del cliente
*user_name: nombre del cliente
*/
void* listening_thread(void* args){
    listening_arguments* arguments = (listening_arguments*)args;
    char incoming_message[MAX_SIZE];
    while(1){
        int read_bytes = read(arguments->client_fd, incoming_message, sizeof(incoming_message));
        if(read_bytes > 0) {
            incoming_message[read_bytes] = '\0'; // Aseguramos que la cadena termine en nulo
            color_format(incoming_message, arguments->user_name);
        }
        else{
            printf("\nconexión terminada");
            close(arguments->client_fd);
            break;
        }
    }
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

//size_t argc, char *argv[]
void main(){
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