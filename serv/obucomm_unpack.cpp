#include "unpack.h"
struct OBUComm OBUCommunpack(char *recvbuf)
{
    struct OBUComm OBUCommdata;
    memset(&OBUCommdata,0,sizeof(OBUCommdata));
    OBUCommdata.CCLength = *(int8_t*)(recvbuf);
    OBUCommdata.ReceiveTimeStampMillisecond.tv_sec = ntohl(*(int32_t*)(recvbuf+1));
    OBUCommdata.ReceiveTimeStampMillisecond.tv_usec = ntohs(*(int16_t*)(recvbuf+5));
    OBUCommdata.CCType = *(int8_t*)(recvbuf+7);
    OBUCommdata.MsgType = *(int8_t*)(recvbuf+8);
    OBUCommdata.MsgCnt = *(int8_t*)(recvbuf+9);
    char bu[100] = {0};
    sscanf(recvbuf+10,"%s",bu);
    OBUCommdata.HardwareSeqNo = atoi(bu);
    return OBUCommdata;
}
