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
    int number_of_clients = 2;
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
    
    int i = 0;int connected_clients = 0;
    while(connected_clients < number_of_clients) {

        Client* new_client = (Client*)malloc(sizeof(Client));
        new_client->addr_len = sizeof(struct sockaddr_in);

        printf("Esperando cliente #%d...\n", connected_clients + 1);

        int fd = accept(server_fd, (struct sockaddr *)&new_client->client_address, &new_client->addr_len);

        if (fd < 0) {
            perror("Error al aceptar");
            free(new_client);
            continue; 
        }

        new_client->client_fd = fd;
    
        List* new_node = (List*)malloc(sizeof(List));
        new_node->user = new_client;
        new_node->next = clients_stack;
        clients_stack = new_node;

        connected_clients++;
    }

    threads_list* thread_list = NULL;
    threads_list* temporal_threads_list;
    thread_args args[connected_clients]; 
    i = 0;
    while(i<connected_clients){
        add_thread(&thread_list);
        i++;
    }
    List* temporal_client_list = clients_stack;
    i = 0;
    while(temporal_client_list != NULL){
        args[i].server_fd = server_fd;
        args[i].client = temporal_client_list->user;
        temporal_client_list = temporal_client_list->next;
        i++;
    }
    i = 0;
    temporal_threads_list = thread_list;
    while(temporal_threads_list != NULL){
        pthread_create(&temporal_threads_list->thread, NULL, register_login, &args[i]);
        temporal_threads_list = temporal_threads_list->next;
        i++;
    }
    temporal_threads_list = thread_list;
    int* partial_result;
    int results[connected_clients];
    i = 0;
    while(temporal_threads_list!=NULL){
        pthread_join(temporal_threads_list->thread, (void**)&partial_result);
        temporal_threads_list = temporal_threads_list->next;
        results[i] = *partial_result;
        i++;
    }
    
    temporal_client_list = clients_stack;
    i = 0;
    List* curr = clients_stack;
    List* prev = NULL;

    while (curr != NULL && i < connected_clients) {
        if (results[i] != 1) {
            if (prev == NULL) {
                clients_stack = curr->next;
            } else {
                prev->next = curr->next;
            }
            close(curr->user->client_fd);
            free(curr->user);
            List* temp = curr;
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
        i++;
    }
    show_list(clients_stack);
    close_sockets(&clients_stack);
}