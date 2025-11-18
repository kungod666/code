#include <stdio.h>

int add(int *x, int *y) {

    return *x + *y;

}

int main() {

    int m = 3, n = 4;

    printf("%d", add(&m, &n));

    return 0;

}
