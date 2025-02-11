#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>  // Use this header on Windows

#define PORT 8080
#define BUFFER_SIZE 1024

void chat(SOCKET client_sock) {
    char buffer[BUFFER_SIZE];
    int n;

    while(1) {
        ZeroMemory(buffer, BUFFER_SIZE);

        // Receive message from client
        n = recv(client_sock, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            printf("Client disconnected or error.\n");
            break;
        }

        printf("Client: %s\n", buffer);

        // Check if the message is "Terminate" to break the loop
        if (strcmp(buffer, "Terminate") == 0) {
            printf("Client has requested to terminate the connection.\n");
            break;
        }

        // Send message back to client
        printf("Server: ");
        ZeroMemory(buffer, BUFFER_SIZE);
        fgets(buffer, sizeof(buffer), stdin);

        // Send message to client
        send(client_sock, buffer, strlen(buffer), 0);
    }
}

int main() {
    WSADATA wsaData;
    SOCKET server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    int client_len;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_sock, 5) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    client_len = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
    if (client_sock == INVALID_SOCKET) {
        printf("Server accept failed\n");
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    printf("Client connected\n");

    // Start chat
    chat(client_sock);

    // Clean up
    closesocket(client_sock);
    closesocket(server_sock);
    WSACleanup();

    return 0;
}
