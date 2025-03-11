#include <stdio.h>
#include <stdlib.h>

int main() {
    int ns, ncs, timestamp, site;
    printf("Enter number of sites: ");
    scanf("%d", &ns);
    printf("Enter number of sites which want to enter critical section: ");
    scanf("%d", &ncs);

    int ts[ns], request[ncs], mp_timestamp[ncs], mp_site[ncs], deferred[ns];

    for(int i = 0; i < ns; i++) {
        ts[i] = 0;
        deferred[i] = 0;
    }

    for(int i = 0; i < ncs; i++) {
        printf("\nEnter timestamp: ");
        scanf("%d", &timestamp);
        printf("Enter site number: ");
        scanf("%d", &site);
        ts[site - 1] = timestamp;
        request[i] = site;
        mp_timestamp[i] = timestamp;
        mp_site[i] = site;
    }

    printf("\nSites and Timestamp:\n");
    for(int i = 0; i < ns; i++) {
        printf("%d %d\n", i + 1, ts[i]);
    }

    for(int i = 0; i < ncs; i++) {
        printf("\nRequest from site: %d\n", request[i]);
        for(int j = 0; j < ns; j++) {
            if(request[i] != (j + 1)) {
                if(ts[j] > ts[request[i] - 1] || ts[j] == 0) {
                    printf("%d Replied\n", j + 1);
                } else {
                    printf("%d Deferred\n", j + 1);
                    deferred[j] = request[i];
                }
            }
        }
    }

    for(int i = 0; i < ncs - 1; i++) {
        for(int j = 0; j < ncs - i - 1; j++) {
            if(mp_timestamp[j] > mp_timestamp[j + 1]) {
                int temp_time = mp_timestamp[j];
                mp_timestamp[j] = mp_timestamp[j + 1];
                mp_timestamp[j + 1] = temp_time;

                int temp_site = mp_site[j];
                mp_site[j] = mp_site[j + 1];
                mp_site[j + 1] = temp_site;
            }
        }
    }

    printf("\nSites entered Critical Section:\n");
    for(int i = 0; i < ncs; i++) {
        printf("Site %d entered Critical Section\n", mp_site[i]);
        if(deferred[mp_site[i] - 1]) {
            printf("Site %d then checks its deferred array and replies to Site %d\n", mp_site[i], deferred[mp_site[i] - 1]);
            deferred[mp_site[i] - 1] = 0;
        }
    }

    return 0;
}
