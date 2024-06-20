#include <stdio.h>

void foo(int b) {                               
    int a = b - 3;
    int c = a + 3;

    printf("%d\n", c); 
}

int main() {
    foo(10);
    return 0;
}
