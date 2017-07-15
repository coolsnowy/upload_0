#ifndef PACKAGE_H
#define PACKAGE_H

#include "main.h"

void add_head(char framebuf[],char &frameType,int16_t Length,char buf[]);
int16_t Getlen(char *buf,int bufsize);
void frame(char &frametype,char *buf);




#endif // PACKAGE_H
