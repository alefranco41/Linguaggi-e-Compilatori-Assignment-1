#include <stdio.h>

void foo(int a) {                               
    int b = a * 1; //a
    int c = b + 0; //a
    int d = a / 1; //a
    int e = 1 / a; //no opt

    printf("%d%d%d%d\n", b,c,d,e); 
}

int main() {
    foo(10);
    return 0;
}
