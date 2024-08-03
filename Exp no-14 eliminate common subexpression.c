#include <stdio.h>
int main() {
    int a, b, c, d, e, f;
    a = 2 * 3;
    b = 2 * 3 + 1;
    c = 2 * 3 - 1;
    d = 2 * 3;
    e = d + 1;
    f = d - 1;
    printf("Original code results: a = %d, b = %d, c = %d\n", a, b, c);
    printf("Optimized code results: e = %d, f = %d\n", e, f);
    return 0;
}
