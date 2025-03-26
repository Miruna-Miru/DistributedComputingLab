import java.util.*;

public class SuzukiKasami {
    static int numProcesses;
    static int tokenHolder = 0;
    static int[] RN;
    static int[] LN;
    static List<Integer> tokenQueue = new ArrayList<>();
    static Map<Integer, Integer> executionTicks = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter number of processes: ");
        numProcesses = scanner.nextInt();
        RN = new int[numProcesses];
        LN = new int[numProcesses];

        for (int i = 0; i < numProcesses; i++) {
            RN[i] = 0;
            LN[i] = 0;
        }

        for (int i = 0; i < numProcesses; i++) {
            System.out.print("Tick for P[ " + i + "] : ");
            executionTicks.put(i, scanner.nextInt());
        }

        System.out.println("P[0] starts with the token.");
        printState();
        scanner.nextLine(); 

        while (true) {
            System.out.print("Enter P_IDs  : ");
            String input = scanner.nextLine();
            if (input.equals("-1")) {

                break;
            }

            try {
                String[] processIDs = input.split("\\s+");
                List<Integer> newRequests = new ArrayList<>();
               
                for (String idStr : processIDs) {
                    int processID = Integer.parseInt(idStr);
                    if (processID >= 0 && processID < numProcesses) {
                        newRequests.add(processID);
                    } else {
                        System.out.println("Invalid process ID: " + processID);
                    }
                }

                handleRequests(newRequests);

            } catch (NumberFormatException e) {
                System.out.println("Invalid input: " + input);
            }
        }
        scanner.close();
    }

    public static void handleRequests(List<Integer> processes) {
        for (int processID : processes) {
            RN[processID]++;
            System.out.println("P[ " + processID + "] requests CS (SEQ : " + RN[processID] + ")");
           
            if (!tokenQueue.contains(processID)) {
                tokenQueue.add(processID); 
            }
        }
       
        printState();
       
        while (!tokenQueue.isEmpty()) {
            int nextProcess = tokenQueue.get(0);
            if (tokenHolder == nextProcess) {
                executeCS(nextProcess);
            } else {
                System.out.println("Checking if Process " + tokenHolder + " should pass the token...");
                if (RN[nextProcess] > LN[nextProcess]) {
                    passToken(nextProcess);
                } else {
                    System.out.println("P[ " + nextProcess + "] doesn't need token anymore, removing from queue.");
                    tokenQueue.remove(0);
                }
            }
        }
    }

    public static void passToken(int toProcess) {
       // System.out.println("P["+tokenHolder+"] exits CS ");
        System.out.println("Token  P[" + tokenHolder + "] --> P[ " + toProcess+"]");
        tokenHolder = toProcess;
        tokenQueue.remove(Integer.valueOf(toProcess));
        printState();
        executeCS(toProcess);
    }

    public static void executeCS(int processID) {
        System.out.println("P[" + processID + "] enters CS for " + executionTicks.get(processID) + " ticks.");
        for (int i = 1; i <= executionTicks.get(processID); i++) {
            System.out.println("Tick " + i + "...");
        }
        System.out.println("P[ " + processID + "] exits CS.");
        LN[processID] = RN[processID];
        printState();
        checkWaitingProcesses();
    }

    public static void checkWaitingProcesses() {
        while (!tokenQueue.isEmpty()) {
            int nextProcess = tokenQueue.get(0);
            if (RN[nextProcess] > LN[nextProcess]) {
                passToken(nextProcess);
                return;
            } else {
                System.out.println("Process " + nextProcess + " is waiting but doesn't need token anymore.");
                tokenQueue.remove(0);
            }
        }
        System.out.println("No P[i] waiting for token.");
    }

    public static void printState() {
        System.out.println("______________VECTORS______________");
        System.out.println("RN: " + Arrays.toString(RN));
        System.out.println("LN: " + Arrays.toString(LN));
        System.out.println("Token Queue: " + tokenQueue);
        System.out.println("Token is with Process: " + tokenHolder);
        System.out.println("___________________________________");
    }
}