#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int SizeOfArray;
    int *arr;
    int *arr2;
    arr = (int *)malloc(sizeof(int) * 5);
    printf("%p\n", arr);
    for(int i = 0; i < 5; i++){
        arr[i] = i;
    }
    for(int i = 0; i <5; i++){
        printf("%d\n", arr[i]);
    }


    free(arr);
    arr2 = (int *)malloc(sizeof(int) * 6);
    for(int i = 0; i < 5; i++){
        arr2[i] = i + 1;
    }
    for(int i = 0; i <5; i++){
        printf("%d\n", arr[i]);
    }
    printf("%p\n", arr);
    printf("%p\n", arr2);
    printf("%p\n", arr);
    return 0;
}
