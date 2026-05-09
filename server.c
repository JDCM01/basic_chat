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

void main(int argc, char *argv[]){
    List* stack = NULL; 
    char server_port[PORT_SIZE];
    char server_ipv4[IPV4_SIZE];
    char server_ipv6[IPV6_SIZE];
    get_arguments(server_port, argv[1], PORT_SIZE);
    get_arguments(server_ipv4, argv[2], IPV4_SIZE);
    get_arguments(server_ipv6, argv[3], IPV6_SIZE);
    printf("\nEl puerto por el cual escuchara el servidor es: %s \nSu dirección ipv4 es: %s\nSu dirección ipv6 es: %s\n",server_port,server_ipv4,server_ipv6);    
    /*
    *Creando el socket
    *AF_INET: Indica que se usara IPv4. Si se quiere llegara a usar IPv6, sería AF_INET6.
    *SOCK_STREAM: Indica que se llevara a cabo 
    *una conexión TCP. Para UDP se usa SOCK_DGRAM
    *0: Protocolo por defecto osea IP
    */
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

    //creando una nueva estructura para el cliente que se conecte
    struct sockaddr_in client_address;
    socklen_t addr_len = sizeof(client_address);

    //Deteniendo el proceso hasta que alguien se conecte
    int client_fd = accept(server_fd,(struct  sockaddr *)&client_address , &addr_len);

    //capturando el error en caso de que algo falle en la conexión
    if (client_fd < 0) {
        perror("Error al aceptar");
        exit(EXIT_FAILURE);
    }

    printf("\nNuevo cliente conectado");

    //Ahora se pueden hacer writes y reads, write envia y read lee lo recibido
    char message[] = "Hola cliente como estas el dia de hoy";
    char answer[MAX_SIZE];
    
    // se envia un mensaje usando el descriptor del cliente osea lo que retorna el accept
    // Usamos strlen para enviar solo los caracteres necesarios (+1 para el '\0')
    write(client_fd, message, string_length(message) + 1);
    
    // Se lee lo que el cliente mande
    // read devuelve la cantidad de bytes leídos
    int bytes_leidos = read(client_fd, answer, sizeof(answer) - 1);
    if (bytes_leidos > 0) {
        answer[bytes_leidos] = '\0'; // Aseguramos que la cadena termine en nulo
        printf("\nRespuesta por parte del cliente: %s\n", answer);
    }
    
    //cerrando el socket
    close(server_fd);
    close(client_fd);

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
    */