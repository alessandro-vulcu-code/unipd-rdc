#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

int main()
{
    	int i,s,t;
    	FILE* f;
	unsigned char* p;
	char response[1999999];

	struct sockaddr_in server; 

    	f = fopen("pippo.txt", "wt"); 	/*"wt": Indica la modalità di apertura del file. "w" sta per scrittura e "t" sta per modalità testo.
					  Questo significa che il file verrà aperto per la scrittura di testo. Se il file non esiste, 
					verrà creato. Se esiste già, il suo contenuto verrà sovrascritto */
    	if (f == NULL) { 
        	printf("Errore di apertura\n");
        	return 1;
    	}

    	s = socket(AF_INET, SOCK_STREAM, 0); /*    AF_INET: Questo parametro indica il dominio del socket, che in questo caso è AF_INET.
						   Questo dominio specifica che il socket utilizzerà il protocollo IPv4 per la comunicazione di rete.    									SOCK_STREAM: Questo parametro specifica il tipo di socket, che in questo caso è SOCK_STREAM.
						   Questo tipo di socket utilizza il protocollo TCP.
    						0: Questo parametro specifica il protocollo da utilizzare. 
						Poiché stiamo utilizzando IPv4 e TCP, il valore 0 indica al sistema operativo di selezionare 										automaticamente il protocollo appropriato*/

		if (s == -1) {
        	printf("Errno= %d\n", errno);
        	perror("Socket fallita");
        	return 1; 
    	}
    	server.sin_family= AF_INET; //Imposta la famiglia di indirizzi del server su IPv4.
	server.sin_port=htons(80);  //Imposta la porta del server su 80, la porta predefinita per HTTP.
	p=(unsigned char*) &server.sin_addr.s_addr; 	/*Questa istruzione serve a ottenere un puntatore all'indirizzo IP del server dall'oggetto server,
							  che è una struttura di tipo sockaddr_in.
							La struttura sockaddr_in contiene due campi che sono di interesse qui:
    							sin_family: Indica la famiglia di indirizzi, che nel nostro caso è AF_INET per IPv4.
    							sin_addr.s_addr: Questo è il campo che contiene l'indirizzo IP del server*/
							
	p[0]=142; p[1]=250; p[2]=187; p[3]=196;
	t=connect(s,(struct sockaddr*) &server, sizeof(struct sockaddr_in));  /*connect: Questa è la funzione che stabilisce una connessione TCP tra il socket e l'indirizzo specificato.
    										s: È il descrittore del socket che desideriamo connettere al server.
    										(struct sockaddr*) &server: Il secondo argomento è un puntatore a una struttura sockaddr
									       	che rappresenta l'indirizzo del server a cui vogliamo connetterci.
									       	Tuttavia, poiché server è di tipo sockaddr_in, che è una struttura più specifica,
									       	è necessario fare un cast a struct sockaddr* per soddisfare la firma della funzione connect.    													sizeof(struct sockaddr_in): Questo è l'ultimo argomento della funzione connect
									       	e specifica la dimensione in byte della struttura 																				passata come secondo argomento. È importante passare la dimensione corretta della struttura indirizzo
									       	(sockaddr_in) per evitare problemi di accesso alla memoria.*/
	if(t==-1){
		perror("Connect Fallita");
		return 1;
	}
	write(s, "GET /\r\n", 7); 	/*Questo è il messaggio di richiesta HTTP GET che verrà inviato al server.
					  In questo caso, si richiede la risorsa radice del server. 
					  Il \r\n rappresenta una sequenza di escape che indica una nuova riga e viene utilizzato nei protocolli di rete
					  per rappresentare il ritorno a capo e la nuova linea.*/
	for(i=0;t=read(s,response+i,1999999-i);i+=t) {printf("t=%d\n",t);} /*Il ciclo continua ad eseguire finché read legge dati dal socket e
									     restituisce un valore diverso da zero (che indica la fine della 																		trasmissione) o finché non si raggiunge la fine dell'array response.*/
	return 0; 
}

