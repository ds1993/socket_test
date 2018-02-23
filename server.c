#include <poll.h>
#include <signal.h>
#include "common.h"
#include "log.h"

#define MAX_LOG_SIZE 1024
#define MAX_CLIENT_SIZE 1024

void HandleClient(int client_fd);

void HandleClient(int client_fd)
{
	BOOL res = TRUE;
 	while (res == TRUE) {
 		struct pollfd pfd[1];
 		pfd[0].fd = client_fd;
 		pfd[0].events = POLLIN;
 		if (poll(pfd, 1, -1) == -1) {
 			PrintLog("poll fail, error %d %s", errno, strerror(errno));
 			res = FALSE;
 		}
 		else {
 			if (pfd[0].revents & POLLIN != 0) {
 				char data[MAX_DATA_SIZE] = {0};
 				ssize_t data_len = recv(client_fd, data, MAX_DATA_SIZE, 0);
 				if (data_len == 0) {
 					PrintLog("client has been closed!");
 					res = FALSE;
 				}
 				else {
 					PrintLog("receive data:");
 					PrintLog("%s", data);
 				}
 			}
 			else {
 				PrintLog("error revents %d", pfd[0].revents);
 			}
 		}
 	}
}

int main()
{
    int server_fd = 0;
    int res = 0;
    struct sockaddr_in server;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        PrintLog("create socket fail, error %d %s", errno, strerror(errno));
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    res = bind(server_fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if (res < 0) {
        PrintLog("bind fail, error %d %s", errno, strerror(errno));
        close(server_fd);
        exit(1);
    }
    res = listen(server_fd, MAX_CLIENT_SIZE);
    if (res < 0) {
        PrintLog("listen fail, error %d %s", errno, strerror(errno));
        close(server_fd);
        exit(1);
    }
    while (1) {
        int client_fd = 0;
        struct sockaddr_in client;
        socklen_t client_len = (socklen_t)sizeof(struct sockaddr);
        client_fd = accept(server_fd, (struct sockaddr*)&client, &client_len);
        if (client_fd < 0) {
            PrintLog("accept fail, error %d %s", errno, strerror(errno));
        }
        else {
            pid_t pid = fork();
            if (pid > 0) {
                signal(SIGCHLD, SIG_IGN);
            }
            else if (pid == 0) {
                close(server_fd);
                HandleClient(client_fd);
                close(client_fd);
                exit(0);
            }
        }
    }
    return 0;
}
