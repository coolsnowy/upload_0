#ifndef LOG_H
#define LOG_H

#define L_ERROR   (4)
#define L_WARN    (3)
#define L_INFO    (2)
#define L_VERBOSE (1)
#define L_DEBUG   (0)

void InitLogSystem(int level, const char *file);
void Log(int level, const char *fmt, ...);
void CloseLogSystem();
#define Debug(s,...) Log(L_DEBUG, "[%s: %d]" s, __FILE__, __LINE__, ##__VA_ARGS__)



#endif // LOG_H
