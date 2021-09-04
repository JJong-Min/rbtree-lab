#include<stdio.h>

void add_one(int* p) {
    (*p) += 1;

}

int main() {
    int a= 1;
    scanf("%d", &a);
    printf("Before : %d \n", a);
    add_one(&a);
    printf("after : %d \n", a);
}