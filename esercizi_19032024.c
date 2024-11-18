#include <stdio.h>
#include <stdlib.h>

int globalvar=0;

int es1(){
        //analizzo lo stack
        static int s1;
        int s2;
        int *p1;
        int *p2;
        printf("Primo puntatore dello stack %p\n",&s1);
        printf("Secondo puntatore dello stack %p\n",&s2);

        //analizzo lo heap
         p1=(int *)malloc(sizeof(int));
         p2=(int *)malloc(sizeof(int));
        printf("Primo puntatore dell'heap: %p\n",p1);
        printf("Secondo puntatore dell'heap: %p\n",p2);
        return 0;
}
int main(void){
        int p3;
        printf("variabile stack nel main");
        printf("%p\n",&p3);
        es1();
        printf("indirizzo var statica globale");
        printf("%p\n",&globalvar);
        return 0;
}


