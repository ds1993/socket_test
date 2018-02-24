#include <stdio.h>
#include <stdarg.h>
#include "log.h"

#define MAX_LOG_SIZE 1024

void PrintLog(const char* format, ...)
{
    va_list arg;
    char log[MAX_LOG_SIZE] = {0};
    int data_len = 0;
    va_start(arg, format);
    data_len = snprintf(log, MAX_LOG_SIZE, "[%d] ",getpid());
    if (data_len > 0) {
        vsnprintf(&log[data_len], MAX_LOG_SIZE - data_len, format, arg);
        printf("%s\n", log);
    }
    va_end(arg);
}
