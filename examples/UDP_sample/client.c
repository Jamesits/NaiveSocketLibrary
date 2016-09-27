/* 
	NaiveSocketLibrary UDP test client
	Listens on 0.0.0.0:5150
	Sends plain string to server
*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../NaiveSocketLibrary.h"

int main(int argc, char *argv[])
{   
	NSLInit();
    SOCKET sConnection = NSLCreateSocket(AF_INET, SOCK_DGRAM, 0);
    SOCKADDR *peer = NSLCreate3TupleV4("127.0.0.1", 5150);

    printf("Type \"quit\" to exit program.\n");

	while(true)
	{
		char data[1024] = {0};
		char recvBuff[1024] = {0};
		printf("Send >");
		scanf("%1023s", data);
		if(strcmp("quit", data)==0)
			break;
		sendto(sConnection, data, strlen(data)+1, 0, peer, NSL3TupleV4Size);
		socklen_t address_len = NSL3TupleV4SocketLen;
		recvfrom(sConnection, recvBuff, 1024, 0, peer, &address_len);
		printf("Received: %s\n", recvBuff);
	}

    NSLCloseSocket(sConnection);
    NSLEnd();
    return 0;
}