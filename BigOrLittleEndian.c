#include <stdlib.h>
#include <stdio.h>
int main() //Con questo programma vogliamo capire se i dati vengono salvati in memoria con formato BigEndian o Little
{
    short int a = 1; 
    char *p = (char*)&a; // Castiamo l'indirizzo di a in un puntatore a char
    if (*p) // Se il primo byte è 1, allora l'architettura è Little Endian
    {
        printf("Sono un'architettura Little Endian\n");
    }
    else {
        printf("Sono un'architettura Big Endian\n");
    }
    return 0;
}