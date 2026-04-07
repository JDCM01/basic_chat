import socket
import argparse

class ChatClient:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.client_socket = None

    def connect(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.host, self.port))

    def send_message(self, message):
        if self.client_socket:
            self.client_socket.sendall(message.encode('utf-8'))

    def receive_message(self):
        if self.client_socket:
            return self.client_socket.recv(1024).decode('utf-8')

    def close(self):
        if self.client_socket:
            self.client_socket.close()

def main():
    parser = argparse.ArgumentParser(description='Simple TCP Client')
    parser.add_argument('--host', type=str, default='localhost')
    parser.add_argument('--port', type=int, default=8080)

    args = parser.parse_args()
    client = ChatClient(args.host, args.port)

    try:
        client.connect()
        while True:
            message = input("Enter message to send or ctrl + c to exit: ")
            client.send_message(message)
            response = client.receive_message()
            print(f"Received response: {response}")
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        client.close()


if __name__ == "__main__":
    main()