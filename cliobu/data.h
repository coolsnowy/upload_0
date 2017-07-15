#ifndef DATA_H
#define DATA_H
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
#include "log.h"
#include "bsm.h"
#include "readfile.h"
#include "spat.h"
#include "bsm.h"
#include "mapdata.h"
#include "package.h"
#include "udprecv.h"
#include "tcpcli.h"
using namespace std;


struct  OBURegisterdata
{
    char SeqNo[40] = {0};
    char VehType = '0';
};

struct OBURegisterdata OBURegist_init(const char *filepath);
void OBURegister_upload(char *buf);
void OBURegister(char *buf,char &frametype,struct OBURegisterdata OBURegdata );
void OBURegist_ok();

struct OBUBSM
{
    //OBUPACK cacaulate! int CCLength = 0;
    //OBUPACK caculate!   int MsgCnt = 0;
    //OBUPACK caculate!   struct timeval TimestampMillisecond ;
    double Longtitude = 0;
    double Latitude = 0;
    double Elevation = 0;
    double PositionAccuracy = 0;
    double speed = 0;
    double Heading = 0;
    double SteeringWheelAngle = 0;
    int BrakeSystemStatus = 0;
    double Acceleration = 0;
    char TurnSignal = '0';
};
void OBUBSM_upload(char *buf,BsmBlob bsmdata);
struct OBUBSM OBUBSM_init(BsmBlob bsmdata);
void OBUBSM_pack(char *sbuf,char &frametype,int &OBUMsgCnt,struct OBUBSM obubsm);



struct OBUComm
{
    //char CCLength;
    //struct timeval ReceiveTimeStampMillisecond;
    char CCType = '0';
    char MsgType = '0';
    //static int MsgCnt = 0;
    int HardwareSeqNo = 0;
};
void OBUComm_pack(char *sbuf,char &frametype,int &OBUComm_MsgCnt,struct OBUComm OBUCommdata);

void OBUComm_upload(char *buf,BsmBlob bsmdata);
struct OBUComm OBUComm_init(BsmBlob bsmdata);

void OBUComm_upload(char *buf,TrafficLight spatdata);
struct OBUComm OBUComm_init(TrafficLight spatdata);

void OBUComm_upload(char *buf,struct Map mapdata);
struct OBUComm OBUComm_init(struct Map mapdata);







#endif // DATA_H
