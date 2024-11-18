#include <stdio.h>
#include <stdint.h>

struct prova{
    int8_t c; // 1 byte
    int64_t x; // 8 byte
};

int main(){
    struct prova v;
    printf("x = %lx, &x = %lx\n", (unsigned long) &v.c,(unsigned long) &v.x);

    printf("Sizeof(v) = %d\n", sizeof(v)); // 16 per il padding
}

/*
Allineamento e padding:
- Il membro c occupa 1 byte.
- Il membro x deve essere allineato a un indirizzo che sia un multiplo della sua dimensione 
-(8 byte) per garantire un accesso efficiente. Questo significa che tra c e x ci saranno 7 byte di padding.

| c (1 byte) | padding (7 byte) | x (8 byte) |
*/