#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>

typedef struct server_socket{
    char port[5];
    char ipv4[20];
    char ipv6[41];
}server_socket;

typedef struct Node{
    struct Socket* data;
    struct Node* next;
}Node;

/*
*copy_string
*-----------
*funcion para copiar los elementos de una string en otra
*
*argumentos:
*-from_this: string que se debe copiar
*-to_this: lugar donde alojare la copia
*-length: ultima posicion del array
**/
void copy_string(char from_this[], char to_this[], int length){
    int i = 0;
    while(i < length){
        to_this[i] = from_this[i];    
        i++;
    }
}

/*
*get_arguments
*-------------
*
*Esta funcion recorrera un arreglo de caracteres volcando cada uno de 
*los caracteres de argv en string hasta que se de una de las posibles
*condiciones de parada:
*-i alcance la penultima posicion del arreglo sobre el cual estoy volcando la informacion
*-la posicion i del arreglo argv sea EOF indicando un error o final del archivo
*
*
*argumentos:
*-string_length: longitud maxima o ultima posicion de la string en la cual estoy volcando la informacion
*-argv: array de uno de los argumentos pasados por consola
*/
void get_arguments(char string[], char argv[], size_t string_length){
    int i = 0;
    int c;
    while(i < string_length - 1 && argv[i] != EOF){//&& (argv += i) != EOF
        string[i] = argv[i];
        i++;
    }
    string[i] = '\0';
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

void main(size_t argc, char *argv[]){
    struct server_socket* socket = (struct server_socket*)malloc(sizeof(struct server_socket));
    //struct server_socket socket;
    char port[5];
    char ipv4[20];
    get_arguments(port, argv[1], 5);
    get_arguments(ipv4, argv[2], 20);
    //printf("puerto: %s direccion ip: %s", port, ipv4);
    copy_string(port, socket->port, 5);
    copy_string(ipv4, socket->ipv4, 20);
    printf("El puerto a usar sera: %s, La direccion del server es: %s", socket->port, socket->ipv4);
    
}