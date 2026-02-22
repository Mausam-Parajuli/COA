// Booth's Multiplication Algorithm (4-bit signed)

#include <stdio.h>
#include <stdlib.h>

int get(int a)
{
    char ch = 'B';
    int flag = 0;

    if (a == 1)
        ch = 'A';

    do
    {
        printf("ENTER VALUE OF %c: ", ch);
        scanf("%d", &a);

        if (a < 0)
        {
            a = a * -1;
            flag = 1;
        }

        if (8 <= a)
            printf("\n\t INVALID NUMBER. ENTER VALUE (-8 < A < 8)!\n");

    } while (8 <= a);

    if (flag)
        a = a * -1;

    return a;
}

void add(int *a, int *b)
{
    int x, i, c = 0;

    for (i = 3; i >= 0; i--)
    {
        x = a[i];
        a[i] = c ^ x ^ b[i];

        if ((c && x) || (x && b[i]) || (b[i] && c))
            c = 1;
        else
            c = 0;
    }
}

void binary(int x, int *arr)
{
    int i, p = x, c[4] = {0, 0, 0, 1};

    for (i = 0; i < 4; i++)
        arr[i] = 0;

    if (x < 0)
        x = -x;

    i = 3;

    do
    {
        arr[i] = x % 2;
        x = x / 2;
        i--;
    } while (x != 0);

    if (p < 0)
    {
        for (i = 0; i < 4; i++)
            arr[i] = 1 - arr[i];

        add(arr, c);
    }
}

void rshift(int msb, int *y)
{
    int i;
    for (i = 3; i > 0; i--)
        y[i] = y[i - 1];

    y[0] = msb;   // preserve sign bit (arithmetic shift)
}

int main()
{
    int q = 0, i, j;
    int a, b;

    int A[4] = {0, 0, 0, 0};
    int C[4] = {0, 0, 0, 1};

    int Q[4], M[4];
    int temp1[4];
    int ans[8];

    printf("---------------------------------------------------\n");
    printf("\n\t\t BOOTHS MULTIPLICATION ALGORITHM\n");
    printf("---------------------------------------------------\n");

    a = get(1);
    b = get(0);

    binary(a, M);
    binary(b, Q);

    printf("\nOPERATION\tA\tQ\tQ'\tM");
    printf("\nINITIAL\t\t");

    for (i = 0; i < 4; i++) printf("%d", A[i]);
    printf("\t");

    for (i = 0; i < 4; i++) printf("%d", Q[i]);
    printf("\t%d\t", q);

    for (i = 0; i < 4; i++) printf("%d", M[i]);

    for (j = 0; j < 4; j++)
    {
        if ((Q[3] == 0) && (q == 1))
        {
            printf("\nA := A + M\t");
            add(A, M);
        }
        else if ((Q[3] == 1) && (q == 0))
        {
            printf("\nA := A - M\t");

            for (i = 0; i < 4; i++)
                temp1[i] = 1 - M[i];

            add(temp1, C);  // 2's complement
            add(A, temp1);
        }
        else
        {
            printf("\nNo Operation\t");
        }

        for (i = 0; i < 4; i++) printf("%d", A[i]);
        printf("\t");

        for (i = 0; i < 4; i++) printf("%d", Q[i]);
        printf("\t%d\t", q);

        for (i = 0; i < 4; i++) printf("%d", M[i]);

        printf("\nShift\t\t");

        int y = A[3];
        q = Q[3];

        rshift(A[0], A);
        rshift(y, Q);

        for (i = 0; i < 4; i++) printf("%d", A[i]);
        printf("\t");

        for (i = 0; i < 4; i++) printf("%d", Q[i]);
        printf("\t%d\t", q);

        for (i = 0; i < 4; i++) printf("%d", M[i]);
    }

    printf("\n\n---------------------------------------------------\n");
    printf("\nTHE ANSWER IN BINARY IS : ");

    for (i = 0; i < 4; i++) ans[i] = A[i];
    for (i = 0; i < 4; i++) ans[i + 4] = Q[i];

    for (i = 0; i < 8; i++)
        printf("%d", ans[i]);

    printf("\n");

    return 0;
}