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
	
    sockaddr_in peer;
	memset(&peer, 0, sizeof(sockaddr_in));
    peer.sin_family = AF_INET; 
	inet_pton(AF_INET, "127.0.0.1", &peer.sin_addr.s_addr);
    peer.sin_port = htons((u_short)5150); 

    printf("Type \"quit\" to exit program.\n");

	while(true)
	{
		char data[1024] = {0};
		char recvBuff[1024] = {0};
		printf("Send >");
		scanf_s("%1023s", data);
		if(strcmp("quit", data)==0)
			break;
		sendto(sConnection, data, strlen(data)+1, 0, (sockaddr *)&peer, sizeof(peer));
		int peerLen = sizeof(peer);
		recvfrom(sConnection, recvBuff, 1024, 0, (sockaddr *)&peer, &peerLen);
		printf("Received: %s\n", recvBuff);
	}

    NSLCloseSocket(sConnection);
    NSLEnd();
    return 0;
}