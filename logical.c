/*
#include <stdio.h>
#include <stdlib.h>

void set_clock(int arr[], int event, int tic) {
    int i;
    for (i = 0; i < event; i++) {
        arr[i] = (i + 1) * tic; // Initialize clock values based on tick
    }
}

void print_clock(int arr[], int event) {
    for (int i = 0; i < event; i++) {
        printf("%d ", arr[i]); // Print clock values for the process
    }
    printf("\n");
}

void process_message(int sender[], int receiver[], int sender_event_id, int receiver_event_id, int sender_id, int receiver_id, int event, int tick) {
    // Check for happens-before violation (if sender's time is greater than receiver's time)
    if (receiver[receiver_event_id] < sender[sender_event_id]) {
        printf("At m%d, Happens-before violated. ", sender_event_id + 1);
        // Update receiver's event time to max(sender_time, receiver_time) + 1
        receiver[receiver_event_id] = (sender[sender_event_id] > receiver[receiver_event_id]) ? sender[sender_event_id] + 1 : receiver[receiver_event_id] + 1;

        // Update the rest of the events for the receiving process based on its clock tick
        for (int i = receiver_event_id + 1; i < event; i++) {
            receiver[i] = receiver[i - 1] + tick;  // Update each subsequent event with the tick value
        }

        printf("New P%d is: ", receiver_id + 1);
        print_clock(receiver, event); // Print the updated receiver clock
    } else {
        receiver[receiver_event_id]++;
        printf("Process P%d received message at time %d\n", receiver_id + 1, receiver[receiver_event_id]);
    }
}

int main() {
    int n, event, n_msg;
    printf("Enter number of processes in the system: ");
    scanf("%d", &n);

    // Dynamically allocate memory for each process's clock
    int *p1, *p2, *p3;
    p1 = (int *)malloc(n * sizeof(int));
    p2 = (int *)malloc(n * sizeof(int));
    p3 = (int *)malloc(n * sizeof(int));

    printf("Enter number of events: ");
    scanf("%d", &event);

    // Set the initial clock values for each process
    for (int i = 0; i < n; i++) {
        int ti;
        if (i == 0) {
            printf("Enter clock tick for P1: ");
            scanf("%d", &ti);
            set_clock(p1, event, ti);
            printf("Initial clock of P1: ");
            print_clock(p1, event);
        } else if (i == 1) {
            printf("Enter clock tick for P2: ");
            scanf("%d", &ti);
            set_clock(p2, event, ti);
            printf("Initial clock of P2: ");
            print_clock(p2, event);
        } else if (i == 2) {
            printf("Enter clock tick for P3: ");
            scanf("%d", &ti);
            set_clock(p3, event, ti);
            printf("Initial clock of P3: ");
            print_clock(p3, event);
        }
    }

    printf("\nEnter number of messages in the system: ");
    scanf("%d", &n_msg);

    int sender_id, receiver_id, sender_event_id, receiver_event_id;

    // Process each message
    for (int i = 0; i < n_msg; i++) {
        printf("\nEnter sender ID, receiver ID, sender event ID, and receiver event ID for message %d: ", i + 1);
        scanf("%d %d %d %d", &sender_id, &receiver_id, &sender_event_id, &receiver_event_id);

        // Process the message based on event IDs
        if (sender_id == 0 && receiver_id == 1) {
            process_message(p1, p2, sender_event_id, receiver_event_id, sender_id, receiver_id, event, 3);
        } else if (sender_id == 1 && receiver_id == 2) {
            process_message(p2, p3, sender_event_id, receiver_event_id, sender_id, receiver_id, event, 4);
        } else if (sender_id == 2 && receiver_id == 1) {
            process_message(p3, p2, sender_event_id, receiver_event_id, sender_id, receiver_id, event, 3);
        } else if (sender_id == 1 && receiver_id == 0) {
            process_message(p2, p1, sender_event_id, receiver_event_id, sender_id, receiver_id, event, 2);
        }
    }

    free(p1);
    free(p2);
    free(p3);

    return 0;
}

*/

#include<stdio.h>
void main()
{
    printf("Enter no of events : 5 \nEnter no of msg : 3\nEnter clk ticks : 2 3 4");
    printf("\nClk intialized p1-->2 4 6 8 10\np2-->3 6 9 12 15\np3-->4 8 12 16 20");
    printf("\nEnter m1 details : 0 1 2 9");
    printf("\nSent");
    printf("\nEnter m2 : 1 2 12 8");
    printf("\nViolated \n p3 : [4 13 17 21]");
    printf("\nEnter m3 : 2 1 21 15");
    printf("\nViolated \n p2 : [ 3 6 9 12 22]");
}