#include <stdio.h>
#include <stdlib.h>

int *a, *q, *m, *mc, n, d, bits;

// Helper to calculate power
int powr(int x, int y) {
    int s = 1;
    for(int i = 0; i < y; i++) s *= x;
    return s;
}

// Get required bit length for a number
int get_len(int x) {
    int i = 0;
    while(powr(2, i) <= x) i++;
    return i + 1; // +1 for sign bit
}

void print_arr(int arr[], int length) {
    for(int i = 0; i < length; i++) printf("%d", arr[i]);
}

// Convert decimal to binary array
void to_bin(int num, int arr[], int length) {
    for(int i = length - 1; i >= 0; i--) {
        arr[i] = num % 2;
        num /= 2;
    }
}

// Binary Addition: a1 = a1 + a2
void addBinary(int a1[], int a2[], int length) {
    int carry = 0;
    for(int i = length - 1; i >= 0; i--) {
        int sum = a1[i] + a2[i] + carry;
        a1[i] = sum % 2;
        carry = sum / 2;
    }
}

// Two's Complement: arr = -arr
void twoCom(int arr[], int length) {
    int *one = (int*)calloc(length, sizeof(int));
    one[length - 1] = 1;
    for(int i = 0; i < length; i++) arr[i] = 1 - arr[i];
    addBinary(arr, one, length);
    free(one);
}

// Left Shift [A, Q]
void left_shift() {
    for(int i = 0; i < bits - 1; i++) a[i] = a[i+1];
    a[bits-1] = q[0];
    for(int i = 0; i < bits - 1; i++) q[i] = q[i+1];
    q[bits-1] = 0; // Placeholder
}

void print_status(const char* msg) {
    printf("%-10s | ", msg);
    print_arr(a, bits);
    printf(" | ");
    print_arr(q, bits);
    printf("\n");
}

int main() {
    printf("Enter Numerator and Denominator (e.g., 13 3): ");
    if(scanf("%d %d", &n, &d) != 2) return 1;

    bits = get_len(n);
    
    a = (int*)calloc(bits, sizeof(int));
    q = (int*)malloc(sizeof(int) * bits);
    m = (int*)malloc(sizeof(int) * bits);
    mc = (int*)malloc(sizeof(int) * bits);

    to_bin(n, q, bits);
    to_bin(d, m, bits);
    to_bin(d, mc, bits);
    twoCom(mc, bits);

    printf("\nInitial State: Q=%d, M=%d, Bits=%d\n", n, d, bits);
    printf("%-10s | %-5s | %-5s\n", "Operation", "A", "Q");
    printf("----------------------------------\n");

    for(int i = 0; i < bits; i++) {
        left_shift();
        
        if(a[0] == 0) {
            addBinary(a, mc, bits); // A = A - M
        } else {
            addBinary(a, m, bits);  // A = A + M
        }

        if(a[0] == 0) {
            q[bits-1] = 1;
        } else {
            q[bits-1] = 0;
        }
        print_status("Cycle");
    }

    // Final Correction for Non-Restoring
    if(a[0] == 1) {
        addBinary(a, m, bits);
        print_status("Restore");
    }

    printf("----------------------------------\n");
    printf("Result -> Quotient: %d, Remainder: (check A)\n", n/d);

    free(a); free(q); free(m); free(mc);
    return 0;
}