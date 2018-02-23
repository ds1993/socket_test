#include <string.h>
#include "common.h"
#include "log.h"

#define EXIT_STR "exit\n"

int main()
{
    int sock_fd;
    struct sockaddr_in server;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        PrintLog("create socket fail, error %d %s", errno, strerror(errno));
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    if (connect(sock_fd, (struct sockaddr*)&server, sizeof(struct sockaddr)) < 0) {
        PrintLog("connect fail, error %d %s", errno, strerror(errno));
        close(sock_fd);
        exit(1);
    }
    BOOL ret = TRUE;
    while (ret == TRUE) {
        char data[MAX_DATA_SIZE] = {0};
        printf("> ");
        if (fgets(data, MAX_DATA_SIZE, stdin) < 0) {
            PrintLog("get data fail!");
            ret = FALSE;
        }
        else {
            if (strcmp(data, EXIT_STR) == 0) {
                ret = FALSE;
            }
            else {
                if (send(sock_fd, data, sizeof(char) * strlen(data), 0) < 0) {
                    PrintLog("send data fail!");
                }
            }
        }
    }
    close(sock_fd);
}
