#include <stdio.h>

int sum(int x, int y) { return (x + y); }

int mult(int x, int y) { return (x * y); }

int main() {
  int x = 0;
  int y = 1;
  int z = 2;

  printf("x: %d\n", x);
  printf("y: %d\n", y);
  printf("z: %d\n", z);
  sum(x, y);
  printf(mult(x, y));
  printf(sum(x, z));
  return x;
}