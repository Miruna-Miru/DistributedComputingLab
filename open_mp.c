#include <stdio.h>
#include <string.h>
#include <omp.h> // For OpenMP and omp_get_wtime()

#define MAX_DIGITS 5000

void multiply_large_numbers(char num1[], int num2, char result[]) {
    int len1 = strlen(num1);
    int carry = 0;
    char temp[MAX_DIGITS] = {0};

    // Parallelizing multiplication loop
    #pragma omp parallel for shared(num1, temp) private(carry)
    for (int i = len1 - 1; i >= 0; i--) {
        int digit = num1[i] - '0';
        int product = digit * num2 + carry;
        temp[len1 - 1 - i] = (product % 10) + '0';
        carry = product / 10;
    }

    // Handle any remaining carry
    int k = len1;
    while (carry) {
        temp[k++] = (carry % 10) + '0';
        carry /= 10;
    }
    temp[k] = '\0';

    // Reverse the temp string into result
    int temp_len = strlen(temp);
    for (int i = 0; i < temp_len; i++) {
        result[i] = temp[temp_len - i - 1];
    }
    result[temp_len] = '\0';
}

void factorial_large(int n, char result[]) {
    strcpy(result, "1"); // Start with factorial of 0 as 1
    char temp[MAX_DIGITS] = {0};

    for (int i = 2; i <= n; i++) {
        multiply_large_numbers(result, i, temp);

        // Ensure only one thread updates the result
        #pragma omp critical
        {
            strcpy(result, temp);
        }
    }
}

int main() {
    int n;
    char result[MAX_DIGITS] = {0};

    printf("Enter a number to calculate factorial: ");
    scanf("%d", &n);

    // Start measuring time
    double start_time = omp_get_wtime();

    // Calculate factorial
    factorial_large(n, result);

    // End measuring time
    double end_time = omp_get_wtime();

    // Print factorial
    printf("\nFactorial of %d:\n%s\n", n, result);

    // Print execution time
    printf("\nExecution Time: %.6f seconds\n", end_time - start_time);

    return 0;
}