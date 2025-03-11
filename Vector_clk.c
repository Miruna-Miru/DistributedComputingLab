#include <stdio.h>
#include <string.h>

#define N 3 // Number of processes

void displayVector(int clock[N]) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d", clock[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]\n");
}

void sendEvent(int sender, int receiver, int vectorClock[N][N]) {
    vectorClock[sender][sender]++; // Increment sender’s clock
    for (int i = 0; i < N; i++) {
        if (vectorClock[receiver][i] < vectorClock[sender][i]) {
            vectorClock[receiver][i] = vectorClock[sender][i];
        }
    }
    printf("Process P%d sent a message to Process P%d\n", sender + 1, receiver + 1);
    printf("Updated Vector Clocks:\n");
    for (int i = 0; i < N; i++) {
        printf("P%d: ", i + 1);
        displayVector(vectorClock[i]);
    }
}

void internalEvent(int process, int vectorClock[N][N]) {
    vectorClock[process][process]++;
    printf("Process P%d performed an internal event\n", process + 1);
    printf("Updated Vector Clock: ");
    displayVector(vectorClock[process]);
}

int main() {
    int vectorClock[N][N] = {0};
    int choice, p1, p2;
    
    while (1) {
        printf("\n1. Internal Event\n2. Send Message\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter process number (1-3) performing internal event: ");
                scanf("%d", &p1);
                internalEvent(p1 - 1, vectorClock);
                break;
            case 2:
                printf("Enter sender process (1-3) and receiver process (1-3): ");
                scanf("%d %d", &p1, &p2);
                sendEvent(p1 - 1, p2 - 1, vectorClock);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
