#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define MAX_DATA_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;
