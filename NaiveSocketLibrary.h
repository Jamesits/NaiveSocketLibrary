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
  #pragma comment(lib, "Ws2_32.lib")
  /* headers */
  /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>

  /* types */
  /* typedef SOCKET unsigned int; */
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr sockaddr;
//#define inet_pton InetPton
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
SOCKET NSLCreateSocket(int domain, int type, int protocol);
/* free socket */
int NSLCloseSocket(SOCKET sock);
/* validate socket */
bool NSLIsSocketValid(SOCKET socket);

#endif