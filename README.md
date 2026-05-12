# Chat en C

Pequeño chat cliente-servidor desarrollado en lenguaje C.

## Compilación

```bash
gcc server.c -o server -lpthread
gcc client.c -o client -lpthread
```

## Ejecución

```bash
./chat <puerto> <ipv4> <ipv6>
```

## Ejemplo

```bash
./chat 8080 172.16.18.1 2001:acad:cafe::1
```

## Argumentos

- `puerto`: puerto utilizado por el chat
- `ipv4`: dirección IPv4 del cliente
- `ipv6`: dirección IPv6 del cliente

## Requisitos

- GCC
- Linux