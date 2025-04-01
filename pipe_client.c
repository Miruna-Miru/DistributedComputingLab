#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"
#define BUFFER_SIZE 512

int main() {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;

    printf("Connecting to server...\n");

    while (1) {
        hPipe = CreateFile(
            PIPE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL
        );

        if (hPipe != INVALID_HANDLE_VALUE) break;
        
        // If server is down, exit client
        if (GetLastError() == ERROR_PIPE_BUSY || GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf("Server not available. Retrying...\n");
            Sleep(1000);
        } else {
            printf("Error: Could not connect to server. Error Code: %ld\n", GetLastError());
            return 1;
        }
    }

    printf("Connected to server. Start chatting...\n");

    while (1) {
        // Get client input
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        // Send message to server
        if (!WriteFile(hPipe, buffer, strlen(buffer), &bytesWritten, NULL)) {
            printf("Error writing to server. Closing...\n");
            break;
        }

        // If client sends "stop", terminate the connection
        if (strcmp(buffer, "stop") == 0) {
            printf("Client sent stop. Closing connection...\n");
            break;
        }

        // Read response from server
        if (!ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL) || bytesRead == 0) {
            printf("Server disconnected. Closing client...\n");
            break;
        }

        buffer[bytesRead] = '\0';
        printf("Server: %s\n", buffer);
    }

    CloseHandle(hPipe);
    printf("Pipe closed. Client shutting down.\n");

    return 0;
}
