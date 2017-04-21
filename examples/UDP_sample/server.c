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
    static int so_broadcast = TRUE;
   	NSLInit();
	SOCKET sListen = NSLSocket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR *conn = NSLEndpointV4("0.0.0.0", 5150);
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof so_broadcast);
	NSLBindV4(sListen, conn);
	printf("binded, press ^C to quit...\n");

	while(true)
	{
		SOCKADDR_IN clientAddr;
		memset(&clientAddr, 0, sizeof(clientAddr));

		char message[1024] = {0};
		socklen_t address_len = NSLEndpointV4SocketLen;
		int recvBytes = recvfrom(sListen, message, sizeof(message), 0, (struct sockaddr*)&clientAddr, &address_len);
		if(recvBytes <= 0)
		{
			// non-blocking receive will return a -1
			break;
		}
		printf("Received: %s\n", message);
		sendto(sListen, message, recvBytes, 0, (struct sockaddr*)&clientAddr, address_len);
	}

   NSLCloseSocket(sListen);
   free(conn);
   NSLEnd();
   return 0;
}
