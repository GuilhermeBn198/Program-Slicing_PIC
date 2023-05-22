#include <stdio.h>
#include <stdlib.h>

int add(int a, int b) {
  int result;
  /*@ slice pragma stmt; */
  result = a + b;
  return result;
}

int multiply(int a, int b) {
  int result;
  result = a * b;
  /*@ slice pragma expr result; */
  return result;
}

int main(int argc, char *argv[]) {
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  int sum = add(a, b);
  int product = multiply(a, b);

  /*@ slice pragma ctrl; */
  if (product > 10) {
    /*@ assert sum > 0; */
    printf("The product is greater than 10 and the sum is positive.\n");
  } else {
    printf("The product is less than or equal to 10.\n");
  }

  return 0;
}