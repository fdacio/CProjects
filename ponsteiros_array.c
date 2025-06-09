#include <stdio.h>
void main() {

    int numeros[] = {1, 2, 3, 4, 5};
    int *p = numeros;
    while(*p) {
        printf("|N: %d |", *p);
        p++;
    }


}