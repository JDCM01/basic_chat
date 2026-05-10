#ifndef HEADER_H
#define HEADER_H


#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include <unistd.h>

/*Constantes
*-----------
*MAX_SIZE: tamaño maximo de las strings 240 caracteres
*PORT_SIZE: tamaño que tendran las cadenas que almacenen los puertos
*IPV4_SIZE: tamaño que tendran las cadenas que almacenen las direcciones ipv4
*IPV6_SIZE: tamaño que tendran las cadenas que almacenen las direcciones ipv6
*/

#define MAX_SIZE 240
#define NAMES_SIZE 20
#define IPV4_SIZE  16
#define IPV6_SIZE 46
#define PORT_SIZE 5


/*Funciones para el manejo de las strings*/

/*
*color_format
*------------
*Función para darle un color diferente a los mensajes, dependiendo de quien los
*envie, si son mensajes del mismo cliente deben verse de color azul, si son
*mensajes enviados por un cliente distinto de color morado y si son 
*mensajes de parte del servidor deben verse de color amarillo
*validara quien lo envio con ayuda de compare_strings 
*dependiendo del emisor se dara un formato a la salida
*Notas:
*\033 le indica a la consola que debe cambiar el color de la cadena
*\x1B le indica a la consola que debe cambiar el color de la cadena
*[33m] el color sera amarillo
*[34m] el color sera azul
*[35m] el color sera magenta 
*[0m] resetea el color
*
*Argumentos:
*Message: el mensaje al cual se le dara formato para mostrarlo la estructura del mensaje sera:
*"nombre_emisor"':'' '"mensaje"'\0' 
*client_name: nombre del cliente 
*/
void color_format(char message[], char client_name[]);

/*
*extract_from_string
*-------------------
*Función para extraer solo un fragmento de una cadena
*recorrera cada posición del array hasta encontrar un caracter especifico
*o encuentre '\0' para seguridad, e ira copiando en piece cada caracter que encuentre
*
*argumentos:
*string: cadena a la cual extraerle un fragmento
*piece: array donde se guardara la string extraida
*goal_character: caracter que indicara el punto de parada del ciclo deseada
*/
void extract_from_string(const char string[], char piece[], char goal_character);

/*
*check_string
*---------------
*Función para verificar que el cliente no este usando un nombre de usuario ya registrado previamente 
*ira de caracter en caracter dentro del fichero de usuarios hasta encontrar un ';'
*una vez allí comparara lo que ha leido vs la cadena que ha proporcionado el cliente
*en caso de ser iguales retornara un 1, en caso contrario continuara leyendo caracteres
*
*Argumentos:
*string_to_validate: Nombre de usuario o contraseña proporcionado por el cliente 
*file_pointer: puntero al archivo donde se guardaran los nombres de los clientes registrados
*option: Para poder reusar la función se necesita saber si se comprobara contraseña o nombre de 
*usuario, por lo cual option indica si es 0 es es el nombre de usuario 
*y debe ir recorriendo todo el archivo
*si es 1 indica que se comprobara contraseña y solo debe ir hasta que encuentre salto de linea
*o EOF
*
*Retorna:
*1: en caso de que el nombre de usuario ya se encuentre registrado o la contraseña coincida
*0: en caso de que no se encuentre registrado
*/

int check_string(char string_to_validate[], FILE *file_pointer, int option);

/*
*copy_string
*-----------
*funcion para copiar los elementos de una string en otra
*
*argumentos:
*-from_this: string que se debe copiar
*-to_this: lugar donde alojare la copia
*-length: ultima posicion del array
*/
void copy_string(char from_this[], char to_this[], size_t LENGTH);

/*
*from_int_to_char
*----------------
*Función para traducir de entero a caracter, segun la tabla ascii
*
*argumentos:
*character: caracter a traducir
*
*Retorno:
*un caracter que puede ir desde la a hasta z, punto, coma, dos puntos, 
*punto y coma, caracter nulo, salto,
*de linea
*/
char from_int_to_char(int character);

/*
*concatenate_string
*------------------
*Función para agregar mas caracteres al final de una string
*va a recorrer la string hasta que encuentre '\0' o caracter nulo
*que es donde termina la  string y lo reemplazara con el primer caracter
*de la cadena que se agregara, se ira copiando caracter a caracter hasta que 
*se encuentre '\0'
*
*argumentos:
*-this_string: string base
*-plus_this: string que se agregara al final de this_string
*/
void concatenate_string(char this_string[], char plus_this[]);

/*
*compare_strings
*---------------
*Función que comparara todos los caracteres de dos strings, y las recorrea hasta 
*que suceda una de las condiciones de parada:
*-el caracter actual analizado sea '\0' en alguna de las dos cadenas
*-algun caracter sea distinto 
*-se alcance la longitud máxima de las cadenas(MAX_SIZE)
*
*Argumentos:
*string_a: La primera de las dos strings
*string_b: La segunda de las dos strings
*
*Retorna:
*1 si recorre ambas strings hasta encontrar '\0' en ambas cadenas
*0 en cualquier otro caso
*/
int compare_strings(char string_a[], char string_b[]);

/*
* string_length:
* --------------
* Calcula la longitud de una cadena de caracteres recorriendo el arreglo
* hasta encontrar el carácter nulo ('\0') o hasta alcanzar el tamaño máximo
* especificado.
*
* Este límite evita leer fuera del arreglo en caso de que la cadena no esté
* correctamente terminada en '\0'.
*
* Parámetros:
* - string: arreglo de caracteres (cadena)
* - max_length: número máximo de caracteres a inspeccionar
*
* Retorna:
* - La cantidad de caracteres recorridos antes de encontrar '\0'
*   o alcanzar max_length.
*/
int string_length(const char string[], size_t LENGTH);

/*
* get_string
* ----------
* Lee una línea de entrada desde el teclado usando getchar() y la almacena
* en el arreglo 'string'.
*
* La lectura se detiene cuando ocurre alguno de los siguientes casos:
* - Se alcanza el fin de archivo (EOF)
* - Se encuentra un salto de línea ('\n')
* - Se alcanza la longitud máxima permitida (max_length - 1)
*
* Al finalizar, se agrega el carácter nulo ('\0') para indicar el final
* de la cadena.
*
* Parámetros:
* - message: arreglo donde se almacenará la cadena
*/
void get_string(char message[]);

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
*-argument_length: longitud del array argv
*/
void get_arguments(char string[], char argv[], size_t argument_length);

/*Funciones para el manejo de archivos*/
/*login
*------
*Función para comparar una contraseña que entregue el usuario con la que se
*halle en el archivo, se llamara a la función check_string, si la 
*contraseña se encuentra en el archivo la función retornara un 1 y
*se le consedera acceso al usuario al chat
*si se equivoca mas de 3 veces en digitar la contraseña se le denegara el acceso
*
*Argumentos:
*-password: contraseña proporcionada por el cliente
*-file_pointer: Apuntador al archivo users.txt donde se encuentran los usuarios y las contraseñas
*
*Retorno:
*0: Si se deniega el acceso
*1: Si se concede el acceso
*/
int login(FILE *file_pointer);

/*
*register_user
*-------------
*Función para registrar un nombre de usuario en el archivo users.txt
*se le pide una contraseña al usuario para posteriormente insertar al nuevo
*usuario en users.txt  
*
*Argumentos:
*user_name: nombre del usuario a registrar
*file_pointer: apuntador al archivo users.txt  
*/
void register_user(char user_name[], FILE *file_pointer);

/*
*print_from_file
*----------------
*esta funcion va recorrer el archivo hasta que se cumpla la condicion:
*-getc entregue EOF indicando un error o el final del archivo
*
*parametros:
*file_pointer: apuntador al archivo
*/
void print_from_file(FILE *file_pointer);

/*
*insert_into_file
*----------------
*esta funcion va a iterar poniendo caracteres en el archivo hasta que se cumpla una de las condiciones:
*-i alcance la ultima posicion del vector string
*-el caracter actual sea '\0' o caracter nulo
*-putc entregue EOF indicando un error o el final del archivo
*
*parametros:
*file_pointer: apuntador al archivo
*-string: vetor de caracteres a insertar en el archivo
*-max_length: tamaño maximo del vector
*/
void insert_into_file(FILE *file_pointer, const char string[]);

/*Funciones y estructuras para el manejo de listas*/

/*Estructura Client
*------------------
*componentes:
*name: nombre del cliente
*port: puerto en el cual se dara la conversación
*ipv4: dirección del cliente IPv4
*ipv6: dirección del cliente IPv6
*/
typedef struct Client{
    char name[NAMES_SIZE];
    int client_fd;
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
*mostrando el nombre de cada cliente conectado
*hasta que se cumpla la condición de parada que el nodo actual sea igual a NULL osea que no halla nodo 
*
*Argumentos:
*stack: lista de clientes conectados al servidor
*/
void show_list(List* stack);

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
void close_sockets(List** stack);

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
*server_fd:
*stack: Lista de clientes conectados
*/
void add_client(int server_fd, List** stack);

#endif

