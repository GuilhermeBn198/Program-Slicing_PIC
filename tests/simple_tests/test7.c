int add(x, y) {
  x += y;
  return x;
};

int main() {
  int x = 5;
  int y = 10;
  int z = 12;

  printf("Before swap: x = %d, y = %d\n", x, y);
  swap(&x, &y);
  add(x, y);

  for (int i = 0; i < z; i++) {
    x++;
    /*@ slice pragma ctrl; */
  }

  printf("After swap: x = %d, y = %d\n", x, y);

  return 0;
}
