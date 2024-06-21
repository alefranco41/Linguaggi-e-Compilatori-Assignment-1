#include <stdio.h>

void foo(int a) {                               
    int b = a * 1;
    int c = b + 0;
    printf("%d%d\n", b,c); 
}

int main() {
    foo(10);
    return 0;
}
