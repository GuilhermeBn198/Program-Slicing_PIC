#include <assert.h>

int main() {
  double a = 3;
  double b = 4;
  double c = 123;

  //@ assert(b >= 0);

  double d = a / b;
  c = a;

  return 0;
}
