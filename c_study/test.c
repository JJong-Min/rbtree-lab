#include <stdio.h>

int main() {
  char str[] = "1234";
  printf("str: \"%s\"\n", str);
  printf("%p\n", str);
  printf("short hex: 0x%04x\n", *(short *) str);
  printf("int hex: 0x%08x\n", *(int *) str);
  printf("long hex: 0x%016lx\n", *(long *) str);

  char buf[] = "ASDF";
  printf("*buf: '%c' 0x%08x\n", *buf, *(int *) buf);
  printf("*(buf+2): '%c' 0x%08x\n", *(buf+2), *(int *) (buf+2));
  printf("buf+2: \"%s\"\n", buf+2);
  *(buf+1) = (char) 0x42;
  printf("buf: \"%s\"\n", buf);
  int arr[] = {1, 2, 3, 4};
  printf("%p\n", arr);
  printf("%p\n", * (short *) arr);
}