#include <stdio.h>
#include <omp.h>

void useless() {
    int tmp = 0; // Initialize tmp
    #pragma omp parallel for firstprivate(tmp)
    for (int j = 0; j < 1000; ++j) {
        tmp += j; // Each thread has its own copy of tmp
    }
    printf("First private clause : %d\n", tmp); // Prints the value from the main thread, which remains 0
    int tp = 0;
    #pragma omp parallel for firstprivate(tmp)lastprivate(tmp)
    for (int j = 0; j < 1000; ++j)
    tp += j;
    printf("Last private ckause : %d\n", tp);
}

int main() {
    useless();
    return 0;
}
