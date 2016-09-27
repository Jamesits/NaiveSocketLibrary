/* 
	NaiveSocketLibrary TCP test client
	Connects to 127.0.0.1:5150
	Sends hard-coded plain string to server
*/

#include <stdio.h>
#include <string.h> /* for memset() */
#include "../../NaiveSocketLibrary.h"

int main(int argc, char *argv[])
{
	NSLInit();
    SOCKET sClient = NSLCreateSocket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR *conn = NSLCreate3TupleV4("127.0.0.1", 5150);
    NSLConnectV4(sClient, conn);   
		
	char message[1024] = {0};
	int recvSize = recv(sClient, message, 1024, 0);
	printf("Received: %s\n", message);

	char msg_send[] = "NaiveSocketLibrary HELLO";
	send(sClient, msg_send, sizeof(msg_send), 0);
			
    NSLCloseSocket(sClient);
    NSLEnd();
    return 0;
}