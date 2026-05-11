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

    int access;
    char message[] = "Server: Conexión establecida con: \0";
    char answer[NAMES_SIZE];
    char user_name[NAMES_SIZE];
    int read_bytes = read(client_fd, user_name, sizeof(user_name));
    if (read_bytes > 0) {
        user_name[read_bytes] = '\0'; // Aseguramos que la cadena termine en nulo
        copy_string(user_name, new_client->name, NAMES_SIZE);
        concatenate_string(message, user_name, MAX_SIZE);
        color_format(message, "Server\0");
    }
    FILE *file_pointer;
    file_pointer = fopen("users.txt","a+");
    if(check_string(user_name, file_pointer, 0) == 1){
        color_format("Server: Usuario encontrado se procede al login\0", "Server\0");
        access = login(client_fd, file_pointer);
    }
    else{
        color_format("Server: No se encontro al usuario entonces se procede a guardarlo\0", "Server\0");
        register_user(client_fd, user_name, file_pointer);
        access = 1;
    }

    if(access == 1){
        new_node->user = new_client;
        new_node->next = *stack;
        *stack = new_node;
    }
    fclose(file_pointer);
}