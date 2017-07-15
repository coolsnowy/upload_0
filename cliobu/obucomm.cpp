#include "data.h"
extern char frametype;
//BSM
void OBUComm_upload(char *buf,BsmBlob bsmdata)
{
    memset(buf,0,500);
    static int OBUComm_bsm_MsgCnt = 0;
    frametype = 0x24;
    struct OBUComm OBUComm_data =OBUComm_init(bsmdata);
    OBUComm_pack(buf,frametype,OBUComm_bsm_MsgCnt,OBUComm_data);
    frame(frametype,buf);
}
struct OBUComm OBUComm_init(BsmBlob bsmdata)
{
    struct OBUComm OBUCommdata;
    memset(&OBUCommdata,0,sizeof(OBUCommdata));
    /* 0-unknown 1-OBU 2-OBU*/
    OBUCommdata.CCType = '1';
    /*0-unknown 1-BSM 2-SPAT 3-MAP 4-RSI 5-RSM*/
    OBUCommdata.MsgType = '1';
    OBUCommdata.HardwareSeqNo = bsmdata.carId;
    return OBUCommdata;
}

//SPAT
void OBUComm_upload(char *buf,TrafficLight spatdata)
{
    memset(buf,0,500);
    static int OBUComm_spat_MsgCnt = 0;
    frametype = 0x24;
    struct OBUComm OBUComm_data =OBUComm_init(spatdata);
    OBUComm_pack(buf,frametype,OBUComm_spat_MsgCnt,OBUComm_data);
    frame(frametype,buf);
}
struct OBUComm OBUComm_init(TrafficLight spatdata)
{
    struct OBUComm OBUCommdata;
    memset(&OBUCommdata,0,sizeof(OBUCommdata));
    /* 0-unknown 1-OBU 2-OBU*/
    OBUCommdata.CCType = '1';
    /*0-unknown 1-BSM 2-SPAT 3-MAP 4-RSI 5-RSM*/
    OBUCommdata.MsgType = '2';
    OBUCommdata.HardwareSeqNo = spatdata.mapId;
    return OBUCommdata;
}

//MAP
void OBUComm_upload(char *buf,Map mapdata)
{
    memset(buf,0,500);
    static int OBUComm_map_MsgCnt = 0;
    frametype = 0x24;
    struct OBUComm OBUComm_data =OBUComm_init(mapdata);
    OBUComm_pack(buf,frametype,OBUComm_map_MsgCnt,OBUComm_data);
    frame(frametype,buf);
}
struct OBUComm OBUComm_init(Map mapdata)
{
    struct OBUComm OBUCommdata;
    memset(&OBUCommdata,0,sizeof(OBUCommdata));
    /* 0-unknown 1-OBU 2-OBU*/
    OBUCommdata.CCType = '1';
    /*0-unknown 1-BSM 2-SPAT 3-MAP 4-RSI 5-RSM*/
    OBUCommdata.MsgType = '3';
    OBUCommdata.HardwareSeqNo = mapdata.mapId;
    return OBUCommdata;
}

void OBUComm_pack(char *sbuf,char &frametype,int &OBUComm_MsgCnt,struct OBUComm OBUCommdata)
{

    frametype = 0x24;
    char *buf = new char[200];
    memset(buf,0,200);
    int j = 0;
    unsigned int tmpMsgCnt  = (++OBUComm_MsgCnt) %256;
    OBUComm_MsgCnt = tmpMsgCnt;
    struct timeval tm;
    memset(&tm,0,sizeof(tm));
    gettimeofday(&tm,NULL);
    *(int32_t*)(buf+j) = htonl((int32_t)tm.tv_sec);
    j += 4;
    *(int16_t*)(buf+j) = htons((int16_t)tm.tv_usec);
    j += 2;
    *(int8_t*)(buf+j) = static_cast<int8_t>(OBUCommdata.CCType);
    j += 1;
    *(int8_t*)(buf+j) = static_cast<int8_t>(OBUCommdata.MsgType);
    j += 1;
    //printf("%02X \n",static_cast<int8_t>(OBUComm_MsgCnt));
    *(int8_t*)(buf+j) = static_cast<int8_t>(OBUComm_MsgCnt);
    j += 1;
    j += sprintf(buf+j,"%d",OBUCommdata.HardwareSeqNo);
    int CCLength = 0;
    while(*buf && CCLength <200)
    {
        CCLength ++;
        buf++;
    }
    cout<<"CCLength = "<<CCLength<<endl;
    buf -= CCLength;
    *(int8_t*)(sbuf) = static_cast<int8_t>(CCLength);
    for(int i =0;i<CCLength;buf++,i++)
    {
        ++sbuf;
        *sbuf = *buf;
    }sbuf -= CCLength;

}
