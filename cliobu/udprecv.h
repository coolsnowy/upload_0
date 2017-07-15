#ifndef UDPRECV_H
#define UDPRECV_H

#include "log.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <ctype.h>
#include <fstream>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <list>
#include <stdint.h>
#include "dataprocess.h"
#define MAXSELECT 100000
#define MAXLINE 1000

void udprecv(const char *RecvPort);



#endif // UDPRECV_H
