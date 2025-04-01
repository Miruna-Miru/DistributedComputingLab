#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"
#define BUFFER_SIZE 512

int main() {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;

    printf("Creating Named Pipe...\n");

    hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, BUFFER_SIZE, BUFFER_SIZE, 0, NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error: Unable to create pipe. Error Code: %ld\n", GetLastError());
        return 1;
    }

    printf("Waiting for client connection...\n");

    if (!ConnectNamedPipe(hPipe, NULL)) {
        printf("Error: Could not connect to the pipe. Error Code: %ld\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Client connected. Start chatting...\n");

    while (1) {
        // Read message from client
        if (!ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL) || bytesRead == 0) {
            printf("Client disconnected or error occurred. Closing server...\n");
            break;
        }
        
        buffer[bytesRead] = '\0';
        printf("Client: %s\n", buffer);

        // If client sends "stop", terminate the connection
        if (strcmp(buffer, "stop") == 0) {
            printf("Client sent stop. Closing connection...\n");
            break;
        }

        // Get server input and send it to the client
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline

        if (!WriteFile(hPipe, buffer, strlen(buffer), &bytesWritten, NULL)) {
            printf("Error writing to client. Closing...\n");
            break;
        }
    }

    CloseHandle(hPipe);
    printf("Pipe closed. Server shutting down.\n");

    return 0;
}
