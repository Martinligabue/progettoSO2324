#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    int addrlen = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0};
    char *message = "Hello from server";

    // Creazione del socket TCP
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Impostazione dei dettagli del server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Binding del socket all'indirizzo e alla porta
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Ascolto delle connessioni in entrata
    if (listen(server_socket, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accettazione delle connessioni in entrata
    if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Ricezione dei dati dal client
    int valread;
    if ((valread = read(new_socket, buffer, BUFFER_SIZE)) < 0) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    printf("Message from client: %s\n", buffer);

    // Invio di un messaggio di risposta al client
    send(new_socket, message, strlen(message), 0);
    printf("Hello message sent to client\n");

    // Chiusura del socket
    close(new_socket);
    close(server_socket);

    return 0;
}
