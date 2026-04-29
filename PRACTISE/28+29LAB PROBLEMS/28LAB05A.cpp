// Problem A

// Input:
// First line: n, a number (1<=n<=15).
// Second line: k, a number (1<=k<=n).
// Output:
// Print all possible combinations of k digits from (0-n) in descending order.
// Sample Case:
// Input Output
// 5
// 3

// 4 3 2
// 4 3 1
// 4 3 0
// 4 2 1
// 4 2 0
// 4 1 0
// 3 2 1
// 3 2 0
// 3 1 0
// 2 1 0
#include <stdio.h>

int n, k;
int comb[20];      // Array to store current combination (max n=15)
int size_comb = 0; // Current size of combination

void backtrack(int start)
{
    if (size_comb == k)
    {
        for (int i = 0; i < k; i++)
        {
            printf("%d", comb[i]);
            if (i != k - 1)
                printf(" ");
        }
        printf("\n");
        return;
    }
    for (int i = start; i >= 0; i--)
    {
        comb[size_comb] = i;
        size_comb++;
        backtrack(i - 1);
        size_comb--;
    }
}

int main()
{
    scanf("%d", &n);
    scanf("%d", &k);
    backtrack(n - 1);
    return 0;
}