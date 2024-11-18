#include <stdio.h>
#include <stdlib.h>

int a;

int fattoriale(int n){
    int * p;
    p = (int *) malloc(sizeof(int));
    printf("Static %lx, Stack: %lx, Heap: %lx\n", (unsigned long) &a, (unsigned long) &n, (unsigned long) p);    
    if(n == 0){
        return 1;
    }
    else{
        return n * fattoriale(n-1);
    }
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: %s <num>\n", argv[0]);
        return 1;
    }

    printf("Il fattoriale di %d è %d\n", atoi(argv[1]), fattoriale(atoi(argv[1])));
    return 0;
}