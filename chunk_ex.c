#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>

char hbuf[10000];
struct headers{
         char * n;
         char * v;
} h[100];

int main() {
	char * statusline;
	int s,t,i,j,len;
	char response[2000000];
	struct sockaddr_in server;
	unsigned char * p;


	s = socket(AF_INET, SOCK_STREAM, 0 );
	if ( s == -1 ) {
        		printf("Errno = %d (%d)\n",errno,EAFNOSUPPORT);
        		perror("Socket fallita:");
        		return 1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	p= (unsigned char*) &server.sin_addr.s_addr ;
	p[0]=142;p[1]=250;p[2]=187; p[3]=196; // 142.250.187.196
	
	t = connect(s,(struct sockaddr *) &server, sizeof(struct sockaddr_in));
	if ( t == -1) {
        		perror("Connect fallita");
        		return 1;
	}
	char * request = "GET / HTTP/1.1\r\nHost:www.google.com\r\n\r\n";
	write(s,request,strlen(request));
	
	statusline = h[0].n = hbuf;
	for(j=0,i=0; read(s,hbuf+i,1);i++){
        		if((hbuf[i]==':' ) && (h[j].v == NULL)){
                		h[j].v=&hbuf[i+1];
                		hbuf[i]=0;
        		}
        		if(hbuf[i]=='\n' && hbuf[i-1]=='\r'){
                		hbuf[i-1]=0;
                		if(h[j].n[0]==0) break;
                		h[++j].n=&hbuf[i+1];
        		}
	}

	#define CHUNKED -1;
	for(i=0;i<j;i++){
        		printf("%s ----> %s\n",h[i].n,h[i].v);
        		if(!strcmp(h[i].n,"Content-Length")){
                		len = atoi(h[i].v);
                		printf("len = %d\n", len);
        		}
        		if(!strcmp(h[i].n,"Transfer-Encoding")){
                        		if( !strcmp(h[i].v+1,"chunked")){
                                		len = CHUNKED;
                        		}
                		printf("%s / %d",h[i].v+1,len);
        		}
	}
	printf("Lunghezza: %d\n",len);

	char lenbuf[100];
	char crlf[2];
	int k=0;
	int lendec=0;
	do{
        		for(int i=0;read(s,&lenbuf[i],1);i++){
                		if(lenbuf[i-1]=='\r'&&lenbuf[i]=='\n'){
                        			lenbuf[i-1]=0;
                        			break;
                		}
        		}
        		printf("lunghezza del chunk: %s\n",lenbuf);

        		lendec = strtol(lenbuf,NULL,16);

        		printf("lunghezza del chunk in decimale: %d\n",lendec);

        		for(int i=0;t=read(s,&response[k],lendec-i);i+=t,k+=t);
        		read(s,crlf,2);

        		if((crlf[0]=='\r')&& (crlf[1]=='\n')){printf("ok\n");}
	}while(lendec>0);

	response[k]=0;
	printf("%s",response);
}
