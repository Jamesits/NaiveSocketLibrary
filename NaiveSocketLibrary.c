/* 
  NaiveSocketLibrary
  by James Swineson
  https://github.com/Jamesits/NaiveSocketLibrary
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "NaiveSocketLibrary.h"

/* Init and dispose */
int NSLInit(void)
{
  #ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(2,2), &wsa_data);
  #else
    return 0;
  #endif
}

int NSLEnd(void)
{
  #ifdef _WIN32
    return WSACleanup();
  #else
    return 0;
  #endif
}

/* create and close sockets */
SOCKET NSLCreateSocket(int domain, int type, int protocol)
{
  return socket(domain, type, protocol);
}

int NSLCloseSocket(SOCKET socket)
{

  int status = 0;
  #ifdef _NSL_OS_WINDOWS
    status = shutdown(socket, SD_BOTH);
    if (status == 0) { status = closesocket(socket); }
  #endif
  #ifdef _NSL_OS_POSIX
    status = shutdown(socket, SHUT_RDWR);
    if (status == 0) { status = close(socket); }
  #endif
  return status;
}

/* check if a socket is valid */
bool NSLIsSocketValid(SOCKET socket)
{
  #ifdef _NSL_OS_WINDOWS
    return socket != INVALID_SOCKET;
  #endif
  #ifdef _NSL_OS_POSIX
    return socket >= 0;
  #endif
  /* holds some compiler warning */
  return false;
}

const size_t NSL3TupleV4Size = sizeof(struct sockaddr);

struct sockaddr* NSLCreate3TupleV4(const char *restrict address, u_short port)
{
  struct sockaddr_in* conn;
  conn = malloc(sizeof(struct sockaddr_in));
  memset(conn, 0, sizeof(struct sockaddr_in));
  conn->sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &(conn->sin_addr.s_addr));
  conn->sin_port = htons(port);

  return (struct sockaddr*)conn;
}

int NSLBindV4(int socket, const struct sockaddr *address)
{
  return bind(socket, address, NSL3TupleV4Size);
}

int NSLConnectV4(int socket, const struct sockaddr *address)
{
  return connect(socket, address, NSL3TupleV4Size);
}
