
#include <stdio.h>
#include <stdlib.h>

int *a, *q, *m, *mc, n, d, b_len;

int powr(int x, int y) {
    int s = 1, i;
    for(i = 0; i < y; i++) s = s * x;
    return s;
}

// Fixed len to ensure enough bits for the sign and value
int len(int x) {
    int i = 0;
    while(powr(2, i) <= x) i++;
    return i + 1; 
}

void print(int arr[], int n) {
    for(int i = 0; i < n; i++) printf("%d", arr[i]);
}

void bin(int num, int arr[], int length) {
    // Clear array first
    for(int j = 0; j < length; j++) arr[j] = 0;
    int i = length - 1;
    while(num > 0 && i >= 0) {
        arr[i--] = num % 2;
        num /= 2;
    }
}

// Replaced your 'set' with a simpler reverse if needed, 
// but bin() now handles alignment correctly.

void addBinary(int a1[], int a2[]) {
    int carry = 0;
    for(int i = b_len - 1; i >= 0; i--) {
        int sum = a1[i] + a2[i] + carry;
        a1[i] = sum % 2;
        carry = sum / 2;
    }
}

void twoCom(int arr[]) {
    int *one = (int*)malloc(sizeof(int) * b_len);
    for(int i = 0; i < b_len - 1; i++) one[i] = 0;
    one[b_len - 1] = 1;
    
    for(int i = 0; i < b_len; i++) arr[i] = 1 - arr[i];
    addBinary(arr, one);
    free(one);
}

void ls() {
    for(int i = 0; i < b_len - 1; i++) a[i] = a[i+1];
    a[b_len - 1] = q[0];
    for(int i = 0; i < b_len - 1; i++) q[i] = q[i+1];
    q[b_len - 1] = 0; 
}

void printaq() {
    print(a, b_len);
    printf("\t");
    print(q, b_len);
    printf("\n");
}

int main() {
    printf("Enter The Numerator/Denominator (e.g. 11/3): ");
    scanf("%d/%d", &n, &d);

    b_len = len(n);
    
    a = (int*)calloc(b_len, sizeof(int));
    q = (int*)malloc(sizeof(int) * b_len);
    m = (int*)malloc(sizeof(int) * b_len);
    mc = (int*)malloc(sizeof(int) * b_len);

    bin(n, q, b_len);
    bin(d, m, b_len);
    bin(d, mc, b_len);
    twoCom(mc);

    int cnt = b_len;
    printf("\nOp\t A\t Q\t Count\n");
    printf("--------------------------------------\n");

    while(cnt > 0) {
        ls();
        printf("LSHIFT\t "); printaq();

        if(a[0] == 0) {
            addBinary(a, mc);
            printf("A=A-M\t ");
        } else {
            addBinary(a, m);
            printf("A=A+M\t ");
        }
        printaq();

        if(a[0] == 0) q[b_len - 1] = 1;
        else q[b_len - 1] = 0;

        printf("SET Q0\t "); printaq();
        cnt--;
        printf("\n");
    }

    // Non-restoring final step
    if(a[0] == 1) {
        addBinary(a, m);
        printf("RESTORE\t "); printaq();
    }

    free(a); free(q); free(m); free(mc);
    return 0;
}