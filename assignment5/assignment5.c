#include <stdio.h>

int *f1(int *val) {
  return val;
}

int main()
{
  int val = 5;
  int *result = f1(&val);
  printf("Value %d is at %p\n", *result, result);
}