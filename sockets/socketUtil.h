#ifndef SOCKET_UTIL
#define SOCKET_UTIL

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>

int createTCPIpv4Socket();
struct sockaddr_in *createTCPIpv4Address(char*,int);

#endif