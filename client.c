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
    
    char message[MAX_SIZE];
    char answer[] = "Excelente ahora que me pude conectar";

    //recibiendo y enviando mensajes al server
    int read_bytes = read(client_fd, answer, sizeof(answer) - 1);
    if (read_bytes > 0) {
        answer[read_bytes] = '\0'; // Aseguramos que la cadena termine en nulo
        printf("\nRespuesta por parte del cliente: %s\n", answer);
    }

    printf("\nEl servidor ha enviado el siguiente mensaje: %s", message);

    write(client_fd, answer, string_length(answer) + 1);

    close(client_fd);

}