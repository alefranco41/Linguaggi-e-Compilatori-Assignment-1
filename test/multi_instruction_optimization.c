#include <stdio.h>

void foo(int b) {                               
    int a = b / 5;
    int c = 5 * a;

    printf("%d\n", c); 
}

int main() {
    foo(10);
    return 0;
}
