#include <stdio.h>

void foo(int b) {                               
    int a = b * 4;
    int c = b * 3;
    int d = b * 5; //no opt
    int e = b / 4;
    int f = b / 5; //no opt
    
    printf("%d%d%d\n", a,c,d); 
}

int main() {
    foo(10);
    return 0;
}
