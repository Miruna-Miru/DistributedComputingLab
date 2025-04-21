#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int process_id;
    int label;
} Process;

void request_resource(Process processes[], int requester, int requested) {
    int old_label = processes[requester].label;

    // Update label of requester based on max(label of requester, label of requested) + 1
    processes[requester].label = (processes[requester].label > processes[requested].label 
                                  ? processes[requester].label 
                                  : processes[requested].label) + 1;

    printf("P%d requests P%d -> Updated P%d label: %d (Old Label: %d)\n",
           processes[requester].process_id, processes[requested].process_id,
           processes[requester].process_id, processes[requester].label, old_label);
}

int transmit_labels(Process processes[], int request_order[][2], int num_requests) {
    printf("\nTransmitting values...\n");

    // Process transmissions in reverse order
    for (int i = num_requests - 1; i >= 0; i--) {  
        int from = request_order[i][0];
        int to = request_order[i][1];

        // Store old values for display
        int old_label = processes[to].label;
        int old_id = processes[to].process_id;

        // Transmit label & process ID
        processes[to].label = processes[from].label;
        processes[to].process_id = processes[from].process_id;
        //ACTUALLY label and ID has to be updated only if new is max than cuurent

        printf("P%d (Label: %d, Process ID: %d) → P%d (Old Label: %d, Old Process ID: %d) → Updated P%d (New Label: %d, New Process ID: %d)\n",
               processes[from].process_id, processes[from].label, processes[from].process_id,
               processes[to].process_id, old_label, old_id,
               processes[to].process_id, processes[to].label, processes[to].process_id);
    }

    // Check for cycle: If any process gets back its original label and ID
    for (int i = 0; i < num_requests; i++) {
        int from = request_order[i][0];
        int to = request_order[i][1];

        if (processes[to].label == processes[from].label &&
            processes[to].process_id == processes[from].process_id) {
            printf("Cycle detected! Deadlock exists.\n");
            return 1;
        }
    }

    printf("No cycle detected.\n");
    return 0;
}

int main() {
    Process processes[MAX_PROCESSES];
    int num_processes, num_requests;

    // Get number of processes
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    // Initialize processes with user-defined values
    printf("\nEnter initial states (Process ID and Label) for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d - Enter Process ID and Label: ", i + 1);
        scanf("%d %d", &processes[i].process_id, &processes[i].label);
    }

    // Print initial states
    printf("\nInitial Process States:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d -> Label: %d, Process ID: %d\n",
               processes[i].process_id, processes[i].label, processes[i].process_id);
    }

    // Get number of resource requests
    printf("\nEnter number of resource requests: ");
    scanf("%d", &num_requests);

    int request_order[num_requests][2];

    // Take resource request inputs
    for (int i = 0; i < num_requests; i++) {
        int requester, requested;
        printf("Enter request (Requester -> Requested) (Process ID format): ");
        scanf("%d %d", &requester, &requested);

        // Find the indices of requester and requested processes
        int requester_index = -1, requested_index = -1;
        for (int j = 0; j < num_processes; j++) {
            if (processes[j].process_id == requester) requester_index = j;
            if (processes[j].process_id == requested) requested_index = j;
        }

        if (requester_index == -1 || requested_index == -1) {
            printf("Invalid Process ID! Try again.\n");
            i--;
            continue;
        }

        request_order[i][0] = requester_index;
        request_order[i][1] = requested_index;

        request_resource(processes, requester_index, requested_index);
    }

    // Transmit values in reverse order and check for cycles
    transmit_labels(processes, request_order, num_requests);

    return 0;
}