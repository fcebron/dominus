#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

void error(char *);

int main(int argc, char *argv[]) {

    // Reading conf from the file 'client.conf':
	FILE* fileData = fopen ("client.conf","r");
	if (fileData == NULL) {
		printf ("ERROR: no data 'client.conf' file found!\n");
		return 1;
	}

	int ierr,
	    port_no;
	ierr = fscanf (fileData,"%d", &(port_no));
	if (ierr != 1) {
		printf ("ERROR: the file is empty\n");
		return 1;
	}
	//printf("Socket read\n");

	char ip[20];
	ierr = fscanf (fileData,"%s", &(ip));
	if (ierr != 1) {
		printf ("ERROR: the file is empty\n");
		return 1;
	}
	printf("ip read\n");
	
	fclose (fileData);





	int sockfd, 
	    newsockfd, 
	    n, 
	    connectfd, 
	    readfd, 
	    writefd;

	char cbuffer[256];
	char *ptr = &cbuffer[0];

	struct sockaddr_in serv_addr;
	struct hostent *he;

	he = gethostbyname(ip);
	if (he == NULL) {
	    error("No Such Host!\n");
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
	    error("Sorry. Socket could not be created!\n");
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr = *((struct in_addr *)he->h_addr);  

	connectfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (connectfd == -1) {
	    error("Sorry. Could not connect to server.\n");
	}

	while(1)
	{   
	    bzero(ptr, sizeof(cbuffer));
	    printf("\nEnter message for Server: \n");
	    gets(cbuffer);
	    writefd = write(sockfd, ptr, sizeof(cbuffer));
	    if (cbuffer[0] == 'q') {
	    	break;
	    }
	    if (writefd == -1) {
	        error("Sorry. Could not send message to Server.");
	    }

	    printf("Congratulations! Server Successfully Received your message.\n");    

	    /*bzero(ptr, sizeof(cbuffer));
	    readfd = read(sockfd, ptr, sizeof(cbuffer));
	    if (readfd == -1)
	        error("Sorry. Message from server could not be read.\n");

	    printf("Message Received: ");
	    puts(cbuffer);*/
	}
	close(sockfd);
	sleep(1);
	return 0;
}


void error(char *msg) {
	perror(msg);
	exit(1);
}
