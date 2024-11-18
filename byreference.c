#include <stdio.h>

void raddoppia(int* x){
    *x = *x * 2; // *x è il valore puntato da x, se usi x stai passando l'indirizzo di x e non il valore
}

int main(){
    int x;
    x = 3;
    raddoppia(&x);

    printf("Vorrei che %d fosse 6\n", x);
}