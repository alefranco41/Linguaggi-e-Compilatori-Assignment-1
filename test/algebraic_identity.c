#include <stdio.h>

void foo(int a) {                               
    int b = a + 0;

    printf("%d\n", b); 
}

int main() {
    foo(10);
    return 0;
}
