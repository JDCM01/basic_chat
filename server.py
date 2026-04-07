import socket
import threading
import argparse

def handle_client(client_socket):
    with client_socket:
        while True:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                break
            print(f"Received message: {message}")
            response = f"Echo: {message}"
            client_socket.sendall(response.encode('utf-8'))


class Server:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def start_server(self):
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind((self.host, self.port))
        server_socket.listen(5)
        print(f"Server listening on {self.host}:{self.port}")

        while True:
            client_socket, addr = server_socket.accept()
            print(f"Connection from {addr}")
            client_handler = threading.Thread(target=handle_client, args=(client_socket,), daemon=True)
            client_handler.start()

def main():
    parser = argparse.ArgumentParser(description='Simple TCP Server')
    parser.add_argument('--host', type=str, default='localhost')
    parser.add_argument('--port', type=int, default=8080)

    args = parser.parse_args()
    server = Server(args.host, args.port)
    server.start_server()

if __name__ == "__main__":
    main()