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


struct  RSURegisterdata
{
    char SeqNo[40] = {0};
    char Name[20] = {0};
    char IpAddress[20] = {0};
    double Latitude = 0;
    double Longitude = 0;
    double Height = 0;
};

struct RSURegisterdata RSURegist_init(const char *filepath);
void RSURegister_upload(char *buf);
void RSURegister(char *buf,char &frametype,struct RSURegisterdata RSURegdata );
void RSURegist_ok();

struct RSUParticipant
{
    //char PTCLength;
    //struct timeval TimeStampMillisecond;
    char PTCType = 0;
    char Source = 0;
    int  PTCId = 0;
    char HardwareSeqNo[30] = {0};
    double Longitude = 0;
    double Latitude = 0;
    double Elevation = 0;
    double PositionAccuracy = 0;
    double Speed = 0 ;
    double Heading = 0;
    double SteeringWheelAngle = 0;
    double BrakeSystemStatus = 0;
    double Acceleration = 0;
    char TurnSignal = 0;
};
void RSUParticipant_upload(char *buf, BsmBlob bsmdata);
void RSUParticipant_pack(char *sbuf,char &frametype,struct RSUParticipant RSUPartdata);
struct RSUParticipant RSUParticipant_init(BsmBlob bsmdata);

struct RSUComm
{
    //char CCLength;
    //struct timeval ReceiveTimeStampMillisecond;
    char CCType = '0';
    char MsgType = '0';
    //static int MsgCnt = 0;
    int HardwareSeqNo = 0;
};
void RSUComm_pack(char *sbuf,char &frametype,int &RSUComm_MsgCnt,struct RSUComm RSUCommdata);

void RSUComm_upload(char *buf,BsmBlob bsmdata);
struct RSUComm RSUComm_init(BsmBlob bsmdata);

void RSUComm_upload(char *buf,TrafficLight spatdata);
struct RSUComm RSUComm_init(TrafficLight spatdata);

void RSUComm_upload(char *buf,struct Map mapdata);
struct RSUComm RSUComm_init(struct Map mapdata);







#endif // DATA_H
