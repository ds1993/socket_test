#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "log.h"

#define MAX_LOG_SIZE 1024

void PrintLog(const char* format, ...)
{
    va_list arg;
    char log[MAX_LOG_SIZE] = {0};
    time_t timep;
    struct tm* time_tm;
    int data_len = 0;
    time_tm = localtime(&timep);
    va_start(arg, format);
    data_len = snprintf(log, MAX_LOG_SIZE, "[%d][%d-%d-%d, %d:%d:%d] ",getpid(), time_tm->tm_year, time_tm->tm_mon, time_tm->tm_mday, time_tm->tm_hour, time_tm->tm_min, time_tm->tm_sec);
    if (data_len > 0) {
        vsnprintf(&log[data_len], MAX_LOG_SIZE - data_len, format, arg);
        printf("%s\n", log);
    }
    va_end(arg);
}
