# include <stdio.h>
/* void형 변수는 존재하지 않음
int main() {
    void a;
    a = 3;
    return 0;
}
*/

/*void type pointer는 단순히 주고값의 보관 역활만 하는 것임*/
int main() {
void *a;
double b = 123.3;

a = &b;
printf("%p\n", a);
/*void pointer의 역참조는 에러발생*/
/*printf("%lf\n", *a);*/
printf("%lf\n", *(double *)a);
}