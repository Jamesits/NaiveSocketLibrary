/* 
	NaiveSocketLibrary UDP test server
	Listens on 0.0.0.0:5150
	Echos everything sent from client.
*/

#include <stdio.h>
#include <stdbool.h>
#include "../../NaiveSocketLibrary.h"

int main(int argc, char *argv[])
{
   	NSLInit();
	SOCKET sListen = NSLCreateSocket(AF_INET, SOCK_DGRAM, 0);
	
	int	port = 5150;
	SOCKADDR_IN local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);    
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	 
	bind(sListen, (SOCKADDR *)&local, sizeof(local));
	printf("Binded...\n");

	while(true)
	{
		SOCKADDR_IN clientAddr;
		memset(&clientAddr, 0, sizeof(clientAddr));
		int clientAddrLen = sizeof(clientAddr);
				
		char message[1024] = {0};
		int recvBytes = recvfrom(sListen, message, sizeof(message), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if(recvBytes <= 0) 
		{
			printf("Client disconnected.\n");
			break;
		}
		printf("Received: %s\n", message);
		sendto(sListen, message, recvBytes, 0, (struct sockaddr*)&clientAddr, clientAddrLen); 
	}

   NSLCloseSocket(sListen);
   NSLEnd();
   return 0;
}
