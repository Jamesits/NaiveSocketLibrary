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
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serverAddr.sin_port = htons((u_short)5150); 

    connect(sClient, (SOCKADDR *)&serverAddr, sizeof(serverAddr));   
		
	char message[1024] = {0};
	int recvSize = recv(sClient, message, 1024, 0);
	printf("%s\n", message);
			
    NSLCloseSocket(sClient);
    
    NSLEnd();
    return 0;
}