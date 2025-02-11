#include <windows.h>
#include <stdio.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"
#define BUFFER_SIZE 512

int main() {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;

    printf("Creating Named Pipe...\n");

    // Create a named pipe
    hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,            // Read/Write access
        PIPE_TYPE_MESSAGE |            // Message-type pipe
        PIPE_READMODE_MESSAGE |        // Message read mode
        PIPE_WAIT,                     // Blocking mode
        1,                             // Max. instances
        BUFFER_SIZE,                   // Output buffer size
        BUFFER_SIZE,                   // Input buffer size
        0,                             // Default timeout
        NULL                           // Default security attributes
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error: Unable to create pipe. Error Code: %ld\n", GetLastError());
        return 1;
    }

    printf("Waiting for client connection...\n");

    // Wait for a client to connect
    if (!ConnectNamedPipe(hPipe, NULL)) {
        printf("Error: Could not connect to the pipe. Error Code: %ld\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Client connected. Waiting for message...\n");

    // Read message from the client
    if (ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';  // Null-terminate the received string
        printf("Received message from client: %s\n", buffer);
    } else {
        printf("Error: Could not read from pipe. Error Code: %ld\n", GetLastError());
    }

    // Send a response to the client
    const char *response = "Hello from server!";
    if (WriteFile(hPipe, response, strlen(response), &bytesWritten, NULL)) {
        printf("Response sent to client: %s\n", response);
    } else {
        printf("Error: Could not write to pipe. Error Code: %ld\n", GetLastError());
    }

    // Close the pipe
    CloseHandle(hPipe);
    printf("Pipe closed. Server shutting down.\n");

    return 0;
}
