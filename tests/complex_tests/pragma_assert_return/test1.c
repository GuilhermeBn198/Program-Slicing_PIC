#include <assert.h>
#include <stdio.h>

int add(int a, int b) {
  //@ slice pragma expr "add";
  int result = a + b;
  return result;
}

int multiply(int a, int b) {
  //@ slice pragma expr "multiply";
  int result = a * b;
  return result;
}

int subtract(int a, int b) {
  int result = a - b;
  return result;
}

int main() {
  int x = 5;
  int y = 10;
  int z = 3;

  int sum = add(x, y);
  int product = multiply(x, y);
  int difference = subtract(x, z);

  //@ assert(y >= x);
  /*@ assert sum == x + y; */;
  printf("Sum: %d\n", sum);
  printf("Product: %d\n", product);
  printf("Difference: %d\n", difference);

  return 0;
}
