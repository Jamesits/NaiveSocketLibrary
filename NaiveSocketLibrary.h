/* 
  NaiveSocketLibrary
  by James Swineson
  https://github.com/Jamesits/NaiveSocketLibrary
*/

#pragma once
#ifndef __NAIVESOCKETLIBRARY_H__
#define __NAIVESOCKETLIBRARY_H__

#ifdef _WIN32
  #define _NSL_OS_WINDOWS
#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #define _NSL_OS_POSIX
#endif

#ifdef _NSL_OS_WINDOWS
  /* headers */
  /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */

  /* Minimum supported Windows version */
  /* Winsock2 (some features) are only available from Windows 8, */
  /* see https://msdn.microsoft.com/en-us/library/windows/desktop/cc805844(v=vs.85).aspx */
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WIN7
  #endif

  /* prevent WIndows.h from including old Winsock.h */
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif

  #include <Winsock2.h>
  #include <WS2tcpip.h>
  #include <Windows.h>

  /* tell linker to get Winsock2 library */
  #pragma comment(lib, "Ws2_32.lib")

  /* types */
  /* 
  typedef unsigned int SOCKET;
  #define inet_pton InetPton
  int inet_pton(int af, const char *src, void *dst);
  typedef struct sockaddr_in SOCKADDR_IN;
  typedef struct sockaddr SOCKADDR;
  */
  typedef struct sockaddr_in sockaddr_in;
  typedef struct sockaddr sockaddr;
#endif
#ifdef _NSL_OS_POSIX
  /* headers */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */

  /* types */
  typedef int SOCKET;
  typedef struct sockaddr_in SOCKADDR_IN;
  typedef struct sockaddr_in sockaddr_in;
  typedef struct sockaddr SOCKADDR;
  typedef struct sockaddr sockaddr;
#endif

#include <stdbool.h>

/* initialize NaiveSocketLibrary */
int NSLInit();
/* dispose NaiveSocketLibrary */
int NSLEnd();
/* create socket */
SOCKET NSLSocket(int domain, int type, int protocol);
/* free socket */
int NSLCloseSocket(SOCKET sock);
/* validate socket */
bool NSLIsSocketValid(SOCKET socket);
/* fill socket endpoint information struct */
extern const size_t NSLEndpointV4Size;
extern const socklen_t NSLEndpointV4SocketLen;
struct sockaddr* NSLEndpointV4(const char *restrict address, u_short port);
/* bind/connect to some 3 tuple */
int NSLBindV4(SOCKET socket, const struct sockaddr *address);
int NSLConnectV4(SOCKET socket, const struct sockaddr *address);
/* send/recv */
/*
ssize_t NSLSend(int socket, const void *buffer, size_t length, int flags);
ssize_t NSLSendToV4(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
ssize_t NSLRecv(int socket, void *buffer, size_t length, int flags);
ssize_t NSLRecvFromV4(int socket, void *restrict buffer, size_t length, int flags, struct sockaddr *restrict address, socklen_t *restrict address_len);
*/
#endif