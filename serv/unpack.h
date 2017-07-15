#ifndef UNPACKAGE_H
#define UNPACKAGE_H

#include <iostream>
#include<stdio.h>
#include<cstdlib>
#include <cstring>
#include <cmath>
#include <list>
#include <arpa/inet.h>
#include "data.h"
#include "log.h"
#define MAXSIZE 100
using namespace std;

struct Mapdata mapunpack(char *buf);

void type_distinguish(char *data_head, char *recvbuf, int sock_fd, int len_not_include_crc);
unsigned char CRC(char* buf, int16_t len);
struct OBURegisterdata OBUReg_unpack(char* recvbuf);
struct OBUBSM bsmunpack(char *recvbuf);
struct OBUComm OBUCommunpack(char *recvbuf);

struct RSURegisterdata RSURegunpack(char *recvbuf);
struct RSUParticipant RSUPartunpack(char *recvbuf);
struct RSUComm RSUCommunpack(char *recvbuf);
TrafficLight spatunpack(char recvbuf[]);
#endif // UNPACKAGE_H
