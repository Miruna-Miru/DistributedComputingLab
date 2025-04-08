#include <stdio.h>

#define MAX 10

int timestamp[MAX][MAX]; // Clock for each process and event
int ticks[MAX];          // Clock increment per process

// Function to get maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to print the timestamp matrix
void printTimestamps(int n, int e[]) {
    printf("\nLamport Clock Matrix:\n");
    for(int i=0;i<n;i++)
        printf("   %d",i);
        printf("\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < e[i]; j++) {
            printf("%d ", timestamp[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n; // number of processes
    int e[MAX]; // events in each process

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter number of events in process P%d: ", i);
        scanf("%d", &e[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("Enter clock tick for process P%d: ", i);
        scanf("%d", &ticks[i]);
    }

    // Initialize clocks
    for (int i = 0; i < n; i++) {
        timestamp[i][0] = ticks[i];
        for (int j = 1; j < e[i]; j++) {
            timestamp[i][j] = timestamp[i][j-1] + ticks[i];
        }
    }

    printTimestamps(n, e);

    int choice;
    do {
        int sp, se, dp, de;
        printf("\nEnter message (Sender Pid Event#, Receiver Pid Event#): ");
        scanf("%d %d %d %d", &sp, &se, &dp, &de);

        if (sp >= n || dp >= n || se >= e[sp] || de >= e[dp]) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (timestamp[dp][de] <= timestamp[sp][se]) {
            printf("Violation of happens-before rule detected!\n");
        }

        // Update clock of receiving event
        timestamp[dp][de] = max(timestamp[dp][de], timestamp[sp][se] + 1);

        // Propagate updates to next events in the same process
        for (int i = de + 1; i < e[dp]; i++) {
            timestamp[dp][i] = timestamp[dp][i-1] + ticks[dp];
        }

        printTimestamps(n, e);

        printf("\nDo you want to enter another message? (1-Yes / 0-No): ");
        scanf("%d", &choice);

    } while (choice == 1);

    return 0;
}
