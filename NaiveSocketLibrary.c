/* 
  NaiveSocketLibrary
  by James Swineson
  https://github.com/Jamesits/NaiveSocketLibrary
*/

#include <stdbool.h>
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
    return s != INVALID_SOCKET;
  #endif
  #ifdef _NSL_OS_POSIX
    return s >= 0;
  #endif
  /* holds some compiler warning */
  return false;
}
