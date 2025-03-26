


#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int Ln[MAX], Rn[MAX], token[MAX], n, tokenHolder;

void broadcastRequest(int pid) {
    printf("P%d Broadcasts Req(%d,%d)\n", pid, pid, Rn[pid] + 1);
    Rn[pid]++;
}

void processRequest(int sender, int receiver) {
    printf("P%d gets Req(%d,%d)\n", receiver, sender, Rn[sender]);
    //Rn[receiver] = Rn[sender];
    printf("P%d updates Rn = [", receiver);
    for (int i = 0; i < n; i++) {
        printf("%d", Rn[i]);
        if (i < n - 1) printf(",");
    }
    printf("]\n");
}

void exitCS(int pid) {
    printf("P%d exits CS\n", pid);
    Ln[pid] = Rn[pid];
    printf("P%d updates Ln = [", pid);
    for (int i = 0; i < n; i++) {
        printf("%d", Ln[i]);
        if (i < n - 1) printf(",");
    }
    printf("]\n");
}

void checkAndSendToken(int pid) {
    for (int i = 0; i < n; i++) {
        if (Rn[i] > Ln[i] && Rn[i] == Ln[i] + 1) {
            printf("P%d checks for Rn[%d] = Ln[%d] + 1\n", pid, i, i);
            printf("P%d sends token to P%d\n", pid, i);
            tokenHolder = i;
            printf("P%d Enters CS\n", i);
            return;
        }
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Ln[i] = 0;
        Rn[i] = 0;
        token[i] = 0;
    }

    int pid;
    printf("Enter Pi which wants CS: ");
    scanf("%d", &pid);
    
    printf("Enter Pi which initially has the token: ");
    scanf("%d", &tokenHolder);
    Rn[tokenHolder]=1;
    
    broadcastRequest(pid);
    
    for (int i = 0; i < n; i++) {
        if (i != pid)
          processRequest(pid, i);
    }

    int exitFlag;
    do {
        printf("Enter 0 if P%d exits CS else -1: ", tokenHolder);
        scanf("%d", &exitFlag);
        
        if (exitFlag == 0) {
            exitCS(tokenHolder);
            checkAndSendToken(tokenHolder);
        } else {
            broadcastRequest(pid);
            for (int i = 0; i < n; i++) {
                if (i != pid) processRequest(pid, i);
            }
        }
    } while (exitFlag != 0);

    return 0;
}
