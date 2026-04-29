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
    for (int i = start; i < n; i++)
    {
        comb[size_comb] = i;
        size_comb++;
        backtrack(i + 1);
        size_comb--;
    }
}

int main()
{
    scanf("%d", &n);
    scanf("%d", &k);
    backtrack(0);
    return 0;
}