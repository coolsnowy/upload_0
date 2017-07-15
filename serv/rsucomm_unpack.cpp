#include "unpack.h"
struct RSUComm RSUCommunpack(char *recvbuf)
{
    struct RSUComm RSUCommdata;
    memset(&RSUCommdata,0,sizeof(RSUCommdata));
    RSUCommdata.CCLength = *(int8_t*)(recvbuf);
    RSUCommdata.ReceiveTimeStampMillisecond.tv_sec = ntohl(*(int32_t*)(recvbuf+1));
    RSUCommdata.ReceiveTimeStampMillisecond.tv_usec = ntohs(*(int16_t*)(recvbuf+5));
    RSUCommdata.CCType = *(int8_t*)(recvbuf+7);
    RSUCommdata.MsgType = *(int8_t*)(recvbuf+8);
    RSUCommdata.MsgCnt = *(int8_t*)(recvbuf+9);
    char bu[100] = {0};
    sscanf(recvbuf+10,"%s",bu);
    RSUCommdata.HardwareSeqNo = atoi(bu);
    return RSUCommdata;
}
