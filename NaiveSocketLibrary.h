/* 
  NaiveSocketLibrary
  by James Swineson
  https://github.com/Jamesits/NaiveSocketLibrary
*/

#pragma once
#ifndef __NAIVESOCKETLIBRARY_H__
#define __NAIVESOCKETLIBRARY_H__

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