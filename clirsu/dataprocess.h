#ifndef DATAPROCESS_H
#define DATAPROCESS_H

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
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <list>
#include "readfile.h"
#include "log.h"
#include "bsm.h"
#include "spat.h"
#include "data.h"
#include "mapdata.h"
#include "udprecv.h"
#include "tcpcli.h"
using namespace std;

void data_process(vector< uint8_t > vec, uint8_t *recvbuf, int recv_num);
void type_distinguish(uint8_t * recvbuf, vector< uint8_t > vec, char * sendbuf, char &frametype, int recv_num);

#endif // DATAPROCESS_H
