#include<stdlib.h>

size_t ipv4_size = 20;
size_t port_size = 4; 
size_t ipv6_size = 41;

/*Estructura Client
*------------------
*componentes:
*port: puerto en el cual se dara la conversación
*ipv4: dirección del cliente IPv4
*ipv6: dirección del cliente IPv6
*/
typedef struct Client{
    char ipv4_address[20];
    char ipv6_address[41];
    char port[4];
}Client;

/*Estructura List
*------------------
*componentes:
*user: apuntador a una estructura Client
*next: apuntador a la misma estructura que guardara la dirección de un siguiente nodo
*/
typedef struct List{
    Client* user;
    struct List* next;
}List;

/*
*show_list
*---------
*función que recorrera una lista compuesta de nodos que seran estructuras Client
*mostrando los elementos de la estructura(puerto, ipv4, ipv6)
*hasta que se cumpla la condición de parada que el nodo actual sea igual a NULL osea que no halla nodo 
*
*Argumentos:
*stack: lista de clientes conectados al servidor
*/
void show_list(List* stack){
    List* actual_node = (List*)malloc(sizeof(List));
    actual_node = stack;
    while(actual_node != NULL){
        printf("\nConexión en el puerto:\t%s, desde la dirección IPv4:\t%s, con dirección IPv6:\t%s", actual_node->user->port, actual_node->user->ipv4_address, actual_node->user->ipv6_address);
        actual_node = actual_node->next;
    }
}

/*
*add_client
*----------
*Función para guardar espacio en memoria para un cliente que tendra dirección ipv4, 6 y puerto
*añadiendolo a la lista, hay dos casos posibles:
*Caso 1, no hay nadie en la lista, en este caso stack sera igual al nuevo nodo creado
*Caso 2, ya hay gente en la lista, por lo cual el componente next de el nodo recien creado
*sera igual al primer nodo de la lista y este nodo recien creado
*sera el nuevo primer elemento de la lista
*
*Argumentos:
*port: puerto en el cual se dara la conversación
*ipv4: dirección del cliente IPv4
*ipv6: dirección del cliente IPv6
*stack: Lista de clientes conectados
*/
void add_client(char port[], char ipv4[], char ipv6[], List** stack){
    Client* new_client = (Client*)malloc(sizeof(Client));
    List* new_node = (List*) malloc(sizeof(List));
    copy_string(ipv4, new_client->ipv4_address, ipv4_size);
    copy_string(ipv6, new_client->ipv6_address, ipv6_size);
    copy_string(port, new_client->port, port_size);
    new_node->user = new_client;
    if(stack == NULL){
        new_node->next = NULL;
        *stack = new_node;
    }
    else{
        new_node->next = *stack;
        *stack = new_node;
    }
}