#include <stdio.h>

void foo(int a, int b, int c) {                               
    //Algebraic Identity
    int r0 = a + 0; //r0 = a
    int r1 = 0 + a; //r1 = a
    int r2 = b * 1; //r2 = b
    int r3 = 1 * b; //r3 = b

    //Strength Reduction
    int r4 = 15 * a; //r4 = (a << 4) - a
    int r5 = a * 15; //r5 = (a << 4) - a
    int r6 = a / 8; // r6 = a >> 3

    //Multi-Instruction Optimization
    int r7 = b + 1;
    int r8 = r7 - 1; // r8 = b

    // Stampa i risultati per mostrare l'effetto delle ottimizzazioni
    printf("r0 = %d\n", r0); //a
    printf("r1 = %d\n", r1); //a
    printf("r2 = %d\n", r2); //b
    printf("r3 = %d\n", r3); //b
    printf("r4 = %d\n", r4); //(a << 4) - a
    printf("r5 = %d\n", r5); //(a << 4) - a
    printf("r6 = %d\n", r6); //a >> 3
    printf("r8 = %d\n", r8); //b
}

int main() {
    foo(24, 5, 2);
    return 0;
}
