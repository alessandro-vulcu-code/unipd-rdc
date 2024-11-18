#include <stdio.h>
#include <stdlib.h> 
unsigned short int htons(unsigned short int input) //questa funzione converte un unsigned short int dal formato little endian al formato big endian
{
	unsigned short int result=((input&0xFF00)>>8)|((input&0x00FF)<<8);
	return result;
}
unsigned long int htonl(unsigned long int input) //questa funzione converte un unsigned long int dal formato little endian al formato big endian
{
	unsigned long int result=((input&0xFF000000)>>24)|((input&0x00FF0000)>>8)|((input&0x0000FF00)<<8)|((input&0x000000FF)<<24);
	return result;
}	
int main()
{
	unsigned short int a=htons(0x1011);			//testing			
	unsigned long int b=htonl(0x12345678);						
	printf("%x\n",b);
}
