#include "log.h"
#include <stdio.h>
#include <stdarg.h>
static int s_level = L_INFO;
static FILE *s_file = NULL;

void InitLogSystem(int level, const char *file)
{
    s_level = level;
    if (file == NULL) {
        s_file = stdout;
        return ;
    }

    s_file = fopen(file, "w");
    if (s_file == NULL) {
        s_file = stdout;
    }

}
void Log(int level, const char *fmt, ...)
{
    static char msgbuf[1024]; // It's enough
    if (level >= s_level) {
        va_list args;
        va_start(args, fmt);
        vsnprintf(msgbuf, sizeof(msgbuf), fmt, args);
        fprintf(s_file, "%s", msgbuf);
        va_end(args);
    }
}

void CloseLogSystem()
{
    if (s_file != stdout) {
        fclose(s_file);
        s_file = stdout;
    }
}
