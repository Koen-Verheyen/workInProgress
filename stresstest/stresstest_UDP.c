#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define SOUND_PORT 80
#define SOUND_GROUP "193.191.150.21"
#define PACKET	   1024
int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    int fd;
    int broadcast = 1;
    int i=0;
    char getal[10];
    char text[PACKET];

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    if((setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof broadcast)) == -1)
    {
        perror("setsockopt - SO_SOCKET ");
        exit(1);
    }


    /* set up destination address */
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SOUND_GROUP);
    addr.sin_port=htons(SOUND_PORT);

    while(1)
    {
         if (sendto(fd, text, strlen(text), 0,(struct sockaddr *) &addr, sizeof(addr)) < 0)
         {
             perror("sendto");
	     exit(1);
         }
    }
}

