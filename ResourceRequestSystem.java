import java.util.*;

public class ResourceRequestSystem {
    static final int MAX_PROCESSES = 10;

    public static void requestResource(int[] processIds, int[] labels, int requesterIndex, int requestedIndex) {
        int oldLabel = labels[requesterIndex];

        // Update label of requester
        labels[requesterIndex] = Math.max(labels[requesterIndex], labels[requestedIndex]) + 1;

        System.out.printf("P%d requests P%d -> Updated P%d label: %d (Old Label: %d)\n",
                processIds[requesterIndex], processIds[requestedIndex],
                processIds[requesterIndex], labels[requesterIndex], oldLabel);
    }

    public static boolean detectCycle(List<List<Integer>> graph, int numProcesses) {
        boolean[] visited = new boolean[numProcesses];
        boolean[] recursionStack = new boolean[numProcesses];

        for (int i = 0; i < numProcesses; i++) {
            if (dfs(graph, i, visited, recursionStack))
                return true;
        }

        return false;
    }

    public static boolean dfs(List<List<Integer>> graph, int node, boolean[] visited, boolean[] stack) {
        if (stack[node]) return true;
        if (visited[node]) return false;

        visited[node] = true;
        stack[node] = true;

        for (int neighbor : graph.get(node)) {
            if (dfs(graph, neighbor, visited, stack))
                return true;
        }

        stack[node] = false;
        return false;
    }

    public static void transmitLabels(int[] processIds, int[] labels, int[][] requestOrder, int numRequests) {
        System.out.println("\nTransmitting values...");

        for (int i = numRequests - 1; i >= 0; i--) {
            int from = requestOrder[i][0];
            int to = requestOrder[i][1];

            int oldLabel = labels[to];
            int oldId = processIds[to];

            // Transmit label & process ID
            labels[to] = labels[from];
            processIds[to] = processIds[from];

            System.out.printf("P%d → P%d (Old Label: %d, Old ID: %d) → Updated P%d (Label: %d, ID: %d)\n",
                    processIds[from], oldId, oldLabel, oldId,
                    processIds[to], labels[to], processIds[to]);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int[] processIds = new int[MAX_PROCESSES];
        int[] labels = new int[MAX_PROCESSES];

        System.out.print("Enter number of processes: ");
        int numProcesses = sc.nextInt();

        System.out.println("\nEnter initial Process ID and Label for each process:");
        for (int i = 0; i < numProcesses; i++) {
            System.out.printf("Process %d - ID and Label: ", i + 1);
            processIds[i] = sc.nextInt();
            labels[i] = sc.nextInt();
        }

        System.out.println("\nInitial Process States:");
        for (int i = 0; i < numProcesses; i++) {
            System.out.printf("P%d -> Label: %d, ID: %d\n", processIds[i], labels[i], processIds[i]);
        }

        System.out.print("\nEnter number of resource requests: ");
        int numRequests = sc.nextInt();

        int[][] requestOrder = new int[numRequests][2];

        // Create graph for cycle detection
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < numProcesses; i++) {
            graph.add(new ArrayList<>());
        }

        for (int i = 0; i < numRequests; i++) {
            int reqId, resId;
            int requesterIndex = -1, requestedIndex = -1;

            System.out.print("Enter request (Requester -> Requested) (Process IDs): ");
            reqId = sc.nextInt();
            resId = sc.nextInt();

            for (int j = 0; j < numProcesses; j++) {
                if (processIds[j] == reqId) requesterIndex = j;
                if (processIds[j] == resId) requestedIndex = j;
            }

            if (requesterIndex == -1 || requestedIndex == -1) {
                System.out.println("Invalid Process ID! Try again.");
                i--;
                continue;
            }

            requestOrder[i][0] = requesterIndex;
            requestOrder[i][1] = requestedIndex;

            graph.get(requesterIndex).add(requestedIndex); // Edge: requester → requested
            requestResource(processIds, labels, requesterIndex, requestedIndex);
        }

        transmitLabels(processIds, labels, requestOrder, numRequests);

        if (detectCycle(graph, numProcesses)) {
            System.out.println("Cycle detected! Deadlock exists.");
        } else {
            System.out.println("No cycle detected.");
        }

        sc.close();
    }
}