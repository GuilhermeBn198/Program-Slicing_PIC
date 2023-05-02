#include <stdio.h>

int foo(int x) {
    return x + 1;
}

int bar(int y) {
    return y * 2;
}

int main() {
    int a = 10;
    int b = 20;
    int c = foo(a) + bar(b);
    printf("%d\n", c);
    return 0;
}
