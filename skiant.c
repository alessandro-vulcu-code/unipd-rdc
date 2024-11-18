#include<stdio.h>

int main(){
/*con questo programma si dimostra che il terminale funziona come stream;
infatti non vengono stampate le due righe*/
	char c[10];
	c[1]=2;
	printf("Ho scritto giusto!");
	c[1000000]=25;
	printf("Ho scritto sbagliato\n");
}
