/* 
	NaiveSocketLibrary TCP test client
	Connects to 127.0.0.1:5150
	Sends plain string to server
*/
#include <stdio.h>
#include <string.h> /* for memset() */
#include "../../NaiveSocketLibrary.h"

int main(int argc, char *argv[])
{
	NSLInit();
    SOCKET sClient = NSLCreateSocket(AF_INET, SOCK_STREAM, 0);
	
    sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET; 
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr);
    serverAddr.sin_port = htons((u_short)5150); 

    connect(sClient, (SOCKADDR *)&serverAddr, sizeof(serverAddr));   
		
	char message[1024] = {0};
	int recvSize = recv(sClient, message, 1024, 0);
	printf("Received: %s\n", message);

	char msg_send[] = "NaiveSocketLibrary HELLO";
	send(sClient, msg_send, sizeof(msg_send), 0);
			
    NSLCloseSocket(sClient);
    
    NSLEnd();
    return 0;
}