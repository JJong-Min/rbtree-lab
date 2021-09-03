#include<stdio.h>

int Add(int a, int b)
{
    int nResult;
    nResult = a + b;
    return nResult;

}

int main(void)
{
    int nResult = 0;
    nResult = Add(10, 5);
    printf("%d", nResult);
}

    
    
