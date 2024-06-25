#include <stdio.h>

void foo(int b) {                               
    int a = b / 5;
    int c = 5 * a;
    
    int d = b + 5;
    int e = d - 5;

    int f = b * 5;
    int g = f / 5;

    int h = b - 5;
    int i = h + 5;


    printf("%d%d%d%d\n", c,e,g,i); 
}

int main() {
    foo(10);
    return 0;
}
