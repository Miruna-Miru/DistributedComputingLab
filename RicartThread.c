#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10

pthread_mutex_t lock;
int ts[MAX];
int deferred[MAX] = {0};
int ns, ncs;

void* site_thread(void* arg) {
    int site = *((int*)arg);

    pthread_mutex_lock(&lock);
    printf("\nRequest from site: %d\n", site);

    for (int j = 0; j < ns; j++) {
        if (site != (j + 1) && ts[j] != 0) { 
            if (ts[site - 1] < ts[j] || 
                (ts[site - 1] == ts[j] && site < (j + 1))) {
                printf("%d Replied\n", j + 1);
            } else {
                printf("%d Deferred\n", j + 1);
                deferred[j] = 1;
            }
        }
    }

    printf("\nSite %d entered Critical Section\n", site);
    sleep(1);

    pthread_mutex_unlock(&lock);  // 🔥 Unlock before replying to deferred requests

    // Now respond to deferred requests
    for (int j = 0; j < ns; j++) {
        if (deferred[j]) {
            printf("Site %d replies to deferred request from Site %d\n", site, j + 1);
            deferred[j] = 0;
        }
    }

    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);

    printf("Enter number of sites: ");
    scanf("%d", &ns);
    printf("Enter number of sites which want to enter critical section: ");
    scanf("%d", &ncs);

    int request[MAX];

    for (int i = 0; i < ns; i++) {
        ts[i] = 0; 
    }

    for (int i = 0; i < ncs; i++) {
        int timestamp, site;
        printf("\nEnter timestamp: ");
        scanf("%d", &timestamp);
        printf("Enter site number: ");
        scanf("%d", &site);
        ts[site - 1] = timestamp;
        request[i] = site;
    }

    printf("\nSites and Timestamp:\n");
    for (int i = 0; i < ns; i++) {
        printf("%d %d\n", i + 1, ts[i]);
    }

    pthread_t threads[MAX];
    
    for (int i = 0; i < ncs - 1; i++) {
        for (int j = i + 1; j < ncs; j++) {
            if (ts[request[i] - 1] > ts[request[j] - 1]) {
                int temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    for (int i = 0; i < ncs; i++) {
        int* site_num = (int*)malloc(sizeof(int));
        *site_num = request[i];
        pthread_create(&threads[i], NULL, site_thread, site_num);
    }

    for (int i = 0; i < ncs; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
