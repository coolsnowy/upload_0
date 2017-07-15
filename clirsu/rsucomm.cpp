#include "data.h"
extern char frametype;
//BSM
void RSUComm_upload(char *buf,BsmBlob bsmdata)
{
    memset(buf,0,500);
    static int RSUComm_bsm_MsgCnt = 0;
    frametype = 0x45;
    struct RSUComm RSUComm_data =RSUComm_init(bsmdata);
    RSUComm_pack(buf,frametype,RSUComm_bsm_MsgCnt,RSUComm_data);
    frame(frametype,buf);
}
struct RSUComm RSUComm_init(BsmBlob bsmdata)
{
    struct RSUComm RSUCommdata;
    memset(&RSUCommdata,0,sizeof(RSUCommdata));
    /* 0-unknown 1-OBU 2-RSU*/
    RSUCommdata.CCType = '1';
    /*0-unknown 1-BSM 2-SPAT 3-MAP 4-RSI 5-RSM*/
    RSUCommdata.MsgType = '1';
    RSUCommdata.HardwareSeqNo = bsmdata.carId;
    return RSUCommdata;
}

//SPAT
void RSUComm_upload(char *buf,TrafficLight spatdata)
{
    memset(buf,0,500);
    static int RSUComm_spat_MsgCnt = 0;
    frametype = 0x45;
    struct RSUComm RSUComm_data =RSUComm_init(spatdata);
    RSUComm_pack(buf,frametype,RSUComm_spat_MsgCnt,RSUComm_data);
    frame(frametype,buf);
}
struct RSUComm RSUComm_init(TrafficLight spatdata)
{
    struct RSUComm RSUCommdata;
    memset(&RSUCommdata,0,sizeof(RSUCommdata));
    /* 0-unknown 1-OBU 2-RSU*/
    RSUCommdata.CCType = '1';
    /*0-unknown 1-BSM 2-SPAT 3-MAP 4-RSI 5-RSM*/
    RSUCommdata.MsgType = '2';
    RSUCommdata.HardwareSeqNo = spatdata.mapId;
    return RSUCommdata;
}

//MAP
void RSUComm_upload(char *buf,Map mapdata)
{
    memset(buf,0,500);
    static int RSUComm_map_MsgCnt = 0;
    frametype = 0x45;
    struct RSUComm RSUComm_data =RSUComm_init(mapdata);
    RSUComm_pack(buf,frametype,RSUComm_map_MsgCnt,RSUComm_data);
    frame(frametype,buf);
}
struct RSUComm RSUComm_init(Map mapdata)
{
    struct RSUComm RSUCommdata;
    memset(&RSUCommdata,0,sizeof(RSUCommdata));
    /* 0-unknown 1-OBU 2-RSU*/
    RSUCommdata.CCType = '1';
    /*0-unknown 1-BSM 2-SPAT 3-MAP 4-RSI 5-RSM*/
    RSUCommdata.MsgType = '3';
    RSUCommdata.HardwareSeqNo = mapdata.mapId;
    return RSUCommdata;
}

void RSUComm_pack(char *sbuf,char &frametype,int &RSUComm_MsgCnt,struct RSUComm RSUCommdata)
{

    frametype = 0x45;
    char *buf = new char[200];
    memset(buf,0,200);
    int j = 0;
    unsigned int tmpMsgCnt  = (++RSUComm_MsgCnt) %256;
    RSUComm_MsgCnt = tmpMsgCnt;
    struct timeval tm;
    memset(&tm,0,sizeof(tm));
    gettimeofday(&tm,NULL);
    *(int32_t*)(buf+j) = htonl((int32_t)tm.tv_sec);
    j += 4;
    *(int16_t*)(buf+j) = htons((int16_t)tm.tv_usec);
    j += 2;
    *(int8_t*)(buf+j) = static_cast<int8_t>(RSUCommdata.CCType);
    j += 1;
    *(int8_t*)(buf+j) = static_cast<int8_t>(RSUCommdata.MsgType);
    j += 1;
    //printf("%02X \n",static_cast<int8_t>(RSUComm_MsgCnt));
    *(int8_t*)(buf+j) = static_cast<int8_t>(RSUComm_MsgCnt);
    j += 1;
    j += sprintf(buf+j,"%d",RSUCommdata.HardwareSeqNo);
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
