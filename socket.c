#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>

FILE * f;

struct sockaddr_in remote;

int main(){
    unsigned char ipserver[] = {142, 250, 180, 3};
    int s;

    if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Error: %d\n", errno);
        perror("Socket fallita");
        return -1;
    }

    remote.sin_family = AF_INET;
    remote.sin_port = htons(80);
    remote.sin_addr.s_addr = *((uint32_t *)ipserver);

    if(connect(s, (struct sockaddr *)&remote, sizeof(remote)) == -1){
        printf("Error: %d\n", errno);
        perror("Connect fallita");
        return -1;
    }
}