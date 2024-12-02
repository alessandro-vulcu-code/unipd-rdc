#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

//printf("%d\n", s);
FILE * f;

struct sockaddr_in remote;
char response[1000001];

int main(){
    int n;
    char * request = "GET / HTTP/1.0\r\n\r\n";
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
    write(s, request, strlen(request));
    size_t len = 0;

    for (len = 0; (n = read(s, response + len, 1000000 - len)) > 0; len +=n);
    if (n == -1)
        {
            printf("Error: %d\n", errno);
            perror("Read fallita");
            return -1;
        }
        printf("%s\n", response);

    close(s);
}