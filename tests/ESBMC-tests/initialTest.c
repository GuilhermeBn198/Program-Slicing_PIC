#include <math.h>

int main() {
  unsigned int N = nondet_uint();  // Initialize unsigned integer N
  double x = nondet_double();      // Initialize double x
  if (x <= 0 ||
      isnan(
          x))  // Check if x is less than or equal to 0 or if x is not a number
    return 0;  // Return 0 if x is less than or equal to 0 or if x is not a
               // number
  unsigned int i = 0;  // Initialize unsigned integer i
  while (i < N) {      // While i is less than N
    x = (2 * x);       // Multiply x by 2
    assert(x > 0);     // Ensure that x is greater than 0
    ++i;               // Increment i by 1
  }
  assert(x > 0);  // Ensure that x is greater than 0
  return 0;       // Return 0
}
