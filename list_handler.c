#include"header.h"

/*
*show_list
*---------
*función que recorrera una lista compuesta de nodos que seran estructuras Client
*mostrando el nombre de cada cliente conectado
*hasta que se cumpla la condición de parada que el nodo actual sea igual a NULL osea que no halla nodo 
*
*Argumentos:
*stack: lista de clientes conectados al servidor
*/
void show_list(List* stack){
    List* actual_node = (List*)malloc(sizeof(List));
    actual_node = stack;
    while(actual_node != NULL){
        printf("\nUsuario: %s", actual_node->user->name);
        actual_node = actual_node->next;
    }
}

/*
*close_sockets
*-------------
*función que recorrera una lista compuesta de nodos que seran estructuras Client
*cerrando los sockets y liberando los espacios 
*en memoria hasta que se cumpla la condición de parada: que el nodo actual
*sea igual a NULL osea que no halla nodo 
*
*Argumentos:
*stack: lista de clientes conectados al servidor
*/
void close_sockets(List** stack){
    if(stack == NULL && *stack == NULL){
        return;
    }

    while(stack != NULL && *stack != NULL){
        List* temp = *stack;
        printf("\nCerrando conexion con: %s", (*stack)->user->name);
        close(temp->user->client_fd);
        *stack = (*stack)->next;
        free(temp->user);
        free(temp);
    }
}

/*
*add_client
*----------
*Función para guardar espacio en memoria para un cliente y agregarlo a la lista 
*de usuarios conectados, hay tres casos posibles a la hora de agregarlo
*Caso 1, no hay nadie en la lista, en este caso stack sera igual al nuevo nodo creado
*Caso 2, ya hay gente en la lista, por lo cual el componente next de el nodo recien creado
*sera igual al primer nodo de la lista y este nodo recien creado
*sera el nuevo primer elemento de la lista
*
*Argumentos:
*server_fd: descriptor de archivo
*stack: Lista de clientes conectados
*/
void add_client(int server_fd, List** stack){
    Client* new_client = (Client*)malloc(sizeof(Client));
    List* new_node = (List*) malloc(sizeof(List));
    
    //creando una nueva estructura para el cliente que se conecte
    struct sockaddr_in client_address;
    socklen_t addr_len = sizeof(client_address);

    //Deteniendo el proceso hasta que alguien se conecte
    int client_fd = accept(server_fd,(struct  sockaddr *)&client_address , &addr_len);

    //capturando el error en caso de que algo falle en la conexión
    if (client_fd < 0) {
        perror("Error al aceptar");
        free(new_client); 
        free(new_node);
        return;
    }

    new_client->client_fd = client_fd;

    char user_name[NAMES_SIZE];
    char message[] = "Hola usuario por favor digite el nombre que desea usar como usuario";

    // se envia un mensaje usando el descriptor del cliente osea lo que retorna el accept
    // Usamos string_length para enviar solo los caracteres necesarios (+1 para el '\0')
    write(client_fd, message, string_length(message, MAX_SIZE));
    
    // Se lee lo que el cliente mande
    // read devuelve la cantidad de bytes leídos
    int bytes_leidos = read(client_fd, user_name, sizeof(user_name));
    if (bytes_leidos > 0) {
        user_name[bytes_leidos] = '\0'; // Aseguramos que la cadena termine en nulo
        copy_string(user_name, new_client->name, string_length(user_name, NAMES_SIZE));
        printf("\nHola %s esperamos te diviertas\n", new_client->name);
    }

    new_node->user = new_client;
    new_node->next = *stack;
    *stack = new_node;

}