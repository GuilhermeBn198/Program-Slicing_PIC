#include <assert.h>

int main() {
  double a = 3;
  double b = 4;
  double c = 123;

  double d = a / b;
  c = a;
  //@ assert(c >= 0);

  return 0;
}
