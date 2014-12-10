#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define BUF_SIZE 2*2048
#define PORT 80

// Funcite om error's af te handelen
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

    char data[BUF_SIZE];
    //Controleren of er genoeg argumenten meegegeven zijn
    if(argc != 2) {
        error("Usage: client <ip of server>\n");
    } 

    //Socket aanmaken
    int sockfd; //socket file descriptor    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Could not create socket\n");
    }
    printf("* Socket created\n");

    //Address struct aanmaken en klaar zetten
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 

    //Tekst ip naar binary ip
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) < 0) {
        error("inet_pton error occured\n");
    } 

    //Connect
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
       error("Failed to make connnection\n");
    }
    printf("* Connection succesful\n");

    //Bericht verzenden
    while(1)
    {
	    send(sockfd,data,BUF_SIZE, 0);

	}

    close(sockfd);

    return 0;
}
