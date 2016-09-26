/* 
	NaiveSocketLibrary UDP test server
	Listens on 0.0.0.0:5150
	Echos everything sent from client.
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../NaiveSocketLibrary.h"

int main(int argc, char *argv[])
{
   	NSLInit();
	SOCKET sListen = NSLCreateSocket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR *conn = NSLCreate3TupleV4("0.0.0.0", 5150);
	NSLBindV4(sListen, conn);
	printf("binded, press ^C to quit...\n");

	while(true)
	{
		SOCKADDR_IN clientAddr;
		memset(&clientAddr, 0, sizeof(clientAddr));
				
		char message[1024] = {0};
		socklen_t address_len = NSL3TupleV4SocketLen;
		int recvBytes = recvfrom(sListen, message, sizeof(message), 0, (struct sockaddr*)&clientAddr, &address_len);
		if(recvBytes <= 0) 
		{
			printf("Client disconnected.\n");
			break;
		}
		printf("Received: %s\n", message);
		sendto(sListen, message, recvBytes, 0, (struct sockaddr*)&clientAddr, address_len); 
	}

   NSLCloseSocket(sListen);
   NSLEnd();
   return 0;
}
