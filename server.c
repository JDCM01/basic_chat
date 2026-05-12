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
#include <unistd.h>
#include<pthread.h>
//Candado para mutex MUTual EXclusion
//pthread_mutex_t lock; 

/*
*main
*----
*
*argumentos:
*-argc: cantidad de argumentos pasados por consola en el caso de este programa debe ser igual a 4
*-argv: array de argumentos pasados por consola, en el caso de este programa los argumentos
*pasados por consola seran puerto y address ipv4 y 6 aunque para pruebas sencillas se 
*ignorara el ipv6, la posicion 0 sera nombre del programa server.c la posicion 1 sera puerto 
*y la posicion 2 sera la address ipv4 en caso de que se este manejando, 
*la posicion 3 del vector sera  address ipv6
*/

//int argc, char *argv[]
void main(){
    int number_of_clients = 1;
    List* clients_stack = NULL;

    /*
    *Creando el socket
    *AF_INET: Indica que se usara IPv4. Si se quiere llegara a usar IPv6, sería AF_INET6.
    *SOCK_STREAM: Indica que se llevara a cabo 
    *una conexión TCP. Para UDP se usa SOCK_DGRAM
    *0: Protocolo por defecto osea IP
    */
    color_format("Server: El servidor se va a detener unos segundos hasta que algun cliente se conecte\0", "Server\0");
    //int* server_fd = (int*)malloc(sizeof(int));
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    //Si el puerto está ocupado por una instancia anterior que acabo de cerrar, déjame reusarlo de inmediato
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    //Dandole identidad al servidor
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Escuchar en todas las IPs disponibles
    address.sin_port = htons(8080);       // El puerto (htons convierte al orden de bytes de red)
    
    //haciendo bind: Cualquier dato que llegue a este puerto específico, dáselo a este programa
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error en bind");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, number_of_clients) == -1){//listen retorna 0 cuando las conexiones son exitosas, -1 si hay errores 
        perror("Error al escuchar a los clientes");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while(i<number_of_clients){
        add_client(&clients_stack);
        i++;
    }

    List* temporal = clients_stack;
    while(temporal != NULL){
        //Deteniendo el proceso hasta que alguien se conecte
        int client_fd = accept(server_fd,(struct  sockaddr *)&temporal->user->client_address, &temporal->user->addr_len);

        //capturando el error en caso de que algo falle en la conexión
        if (client_fd < 0) {
            perror("Error al aceptar");
            temporal->next = temporal->next->next;
            free(temporal); 
        }
        else{
            temporal->user->client_fd = client_fd;
        }
        temporal = temporal->next;
    }

    threads_list* thread_list = NULL;
    threads_list* temp;
    //thread_args* args = (thread_args*)malloc(sizeof(thread_args));
    thread_args args[number_of_clients]; 
    args->server_fd = server_fd;
    args->client = clients_stack->user;
    i = 0;
    while(i<number_of_clients){
        add_thread(&thread_list);
        i++;
    }
    temporal = clients_stack;
    i = 0;
    while(temp != NULL){
        args[i].server_fd = server_fd;
        args[i].client->client_fd = temporal->user->client_fd;
        temporal = temporal->next;
        i++;
    }
    i = 0;
    temp = thread_list;
    while(temp != NULL){
        pthread_create(&temp->thread, NULL, register_login, &args[i]);
        temp = temp->next;
        i++;
    }
    temp = thread_list;
    int* partial_result;
    while(temp!=NULL){
        pthread_join(temp->thread, (void**)&partial_result);
        temp = temp->next;
    }

    //add_client(server_fd, &clients_stack);
    show_list(clients_stack);
    close_sockets(&clients_stack);
}