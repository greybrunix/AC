#include <stdio.h>

void
swap(int v[], int i, int j)
{
    int tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void
bubbleSort(int v[], int N)
{
    int i, j;
    for (i=N-1; i>0; i--)
        for (j=0; j<i;j++)
            if (v[j] > v[j+1]) swap(v,j,j+1);
    return;
} // Best case: O(N) comparisons
  // Worst case: O(N^2) comparisons

void
iSort(int v[], int N)
{
    int i, j;
    for (i=1; i<N; i++)
        for (j=i; j>0 && v[j-1] > v[j]; j--)
            swap(v,j,j-1);
    return;
} // Best Case: O(N) comparisons
  // Worst Case: O(N^2) comparisons


int
main()
{
    return 0;
}
