#include <stdio.h>

void foo(int b) {                               
    int a = b * 8;
    int c = b * 7;
    int d = b * 5; //no opt
    int e = b / 4;
    int f = b / 5; //no opt
    int g = b * 17; 
    printf("%d%d%d%d%d%d\n", a,c,d,e,f,g); 
}

int main() {
    foo(10);
    return 0;
}
