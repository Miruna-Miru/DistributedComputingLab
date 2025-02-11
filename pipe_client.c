#include <windows.h>
#include <stdio.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"
#define BUFFER_SIZE 512

int main() {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;

    printf("Connecting to server...\n");

    // Connect to the named pipe
    hPipe = CreateFile(
        PIPE_NAME,
        GENERIC_READ | GENERIC_WRITE,  // Read/Write access
        0,                             // No sharing
        NULL,                          // Default security attributes
        OPEN_EXISTING,                 // Opens existing pipe
        0,                             // Default attributes
        NULL                           // No template file
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error: Could not connect to server. Error Code: %ld\n", GetLastError());
        return 1;
    }

    printf("Connected to server. Sending message...\n");

    // Send a message to the server
    const char *message = "Hello from client!";
    if (WriteFile(hPipe, message, strlen(message), &bytesWritten, NULL)) {
        printf("Message sent to server: %s\n", message);
    } else {
        printf("Error: Could not write to pipe. Error Code: %ld\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    // Read the response from the server
    if (ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';  // Null-terminate the received string
        printf("Response received from server: %s\n", buffer);
    } else {
        printf("Error: Could not read from pipe. Error Code: %ld\n", GetLastError());
    }

    // Close the pipe
    CloseHandle(hPipe);
    printf("Pipe closed. Client shutting down.\n");

    return 0;
}
