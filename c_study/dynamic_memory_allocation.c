#include <stdio.h>
#include <stdlib.h>
 
int main() {
    int n, m, i;
    int **arr;
    scanf("%d %d", &n,&m);
 
    int *arr = (malloc(sizeof(int)*n));
 
 
    for (i = 0; i<n; i++)
        arr[i] = (int *)malloc(sizeof(int)*m);
 
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &arr[i][j]);
    printf("\n\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("arr[%d][%d]=%d\n", i, j, arr[i][j]);
        printf("\n");
    }
 
    for (i = 0; i<n; i++)
        free(arr[i]);
    free(arr);
 
}