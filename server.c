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
    List* stack = NULL;
    /* 
    char server_port[PORT_SIZE];
    char server_ipv4[IPV4_SIZE];
    char server_ipv6[IPV6_SIZE];
    get_arguments(server_port, argv[1], PORT_SIZE);
    get_arguments(server_ipv4, argv[2], IPV4_SIZE);
    get_arguments(server_ipv6, argv[3], IPV6_SIZE);
    printf("\nEl puerto por el cual escuchara el servidor es: %s \nSu dirección ipv4 es: %s\nSu dirección ipv6 es: %s\n",server_port,server_ipv4,server_ipv6);    
    */
    /*
    *Creando el socket
    *AF_INET: Indica que se usara IPv4. Si se quiere llegara a usar IPv6, sería AF_INET6.
    *SOCK_STREAM: Indica que se llevara a cabo 
    *una conexión TCP. Para UDP se usa SOCK_DGRAM
    *0: Protocolo por defecto osea IP
    */
    color_format("Server: El servidor se va a detener unos segundos hasta que algun cliente se conecte\0", "Server\0");
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

    if(listen(server_fd, 1) == -1){//listen retorna 0 cuando las conexiones son exitosas, -1 si hay errores 
        perror("Error al escuchar a los clientes");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    //while(i<=1){
    add_client(server_fd, &stack);
        //i++;
    //}
    //add_client(server_fd, &stack);
    show_list(stack);
    close_sockets(&stack);
}

/*FILE *file_pointer = fopen("users.txt", "a+");
    fclose(file_pointer);*/

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
    //cerrando el socket
    close(server_fd);
    close(client_fd);
    */