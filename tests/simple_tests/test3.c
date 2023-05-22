#include <stdio.h>

int foo(int x) {
    int y = x * 2;
    return y;
}

int main() {
    int a = 1;
    int b = foo(a);
	int c = 0;
	int d = 1;
	int e = 2;
    printf("b: %d\n", b);
    return 0;
}