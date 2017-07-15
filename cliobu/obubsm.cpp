#include "data.h"
extern char frametype;
void OBUBSM_upload(char *buf,BsmBlob bsmdata)
{
    memset(buf,0,500);
    frametype = 0x22;
    struct OBUBSM obubsmdata = OBUBSM_init(bsmdata);
    static int MsgCnt = 0 ;
    OBUBSM_pack(buf,frametype,MsgCnt,obubsmdata);
    frame(frametype,buf);
}
struct OBUBSM OBUBSM_init(BsmBlob bsmdata)
{
    struct OBUBSM obubsmdata;
    memset(&obubsmdata,0,sizeof(obubsmdata));
    obubsmdata.Longtitude = bsmdata.longitude;
    obubsmdata.Latitude = bsmdata.latitude;
    obubsmdata.Elevation = 0;
    obubsmdata.PositionAccuracy = 0.1;
    obubsmdata.speed = bsmdata.speed;
    obubsmdata.Heading = bsmdata.heading;
    obubsmdata.SteeringWheelAngle = bsmdata.wheelAngle;
    obubsmdata.BrakeSystemStatus = bsmdata.carBrake;
    obubsmdata.Acceleration = bsmdata.acceleration;
    /*1-no turn signal 2 right 3-letf 4-hazard*/
    obubsmdata.TurnSignal = '1';
    return obubsmdata;
}
void OBUBSM_pack(char *sbuf,char &frametype,int &OBUMsgCnt,struct OBUBSM obubsm)
{
    //cout<<"start OBUPack"<<endl;
    frametype = 0x22;
    char *buf = new char[200];
    int j = 0;
    unsigned int tmp_MsgCnt = (++OBUMsgCnt)%256;
    OBUMsgCnt = tmp_MsgCnt;
//    cout<<OBUMsgCnt<<endl;
    *(int8_t*) buf = static_cast<int8_t>(OBUMsgCnt);
    j += 1;
    struct timeval tm;
    memset(&tm,0,sizeof(tm));
    gettimeofday(&tm,NULL);
//    cout<<tm.tv_sec<<'\t'<<tm.tv_usec<<endl;
    *(int32_t*)(buf+j) = htonl((int32_t)tm.tv_sec);
    j += 4;
    *(int16_t *)(buf+j) = htons((int16_t)(tm.tv_usec));
    j += 2;
//    cout<<obubsm.Longtitude<<endl;
    if(obubsm.Longtitude)
    j += sprintf(buf+j,"%f",obubsm.Longtitude);
    j += sprintf(buf+j,"%c",',');
   // cout<<"obubsm Latitude = "<<obubsm.Latitude<<endl;
    if(obubsm.Latitude)
    j += sprintf(buf+j,"%f",obubsm.Latitude);
    j += sprintf(buf+j,"%c",',');

    if(obubsm.Elevation)
    j += sprintf(buf+j,"%f",obubsm.Elevation);
    j += sprintf(buf+j,"%c",',');

    if(obubsm.PositionAccuracy)
    j += sprintf(buf+j,"%f",obubsm.PositionAccuracy);
    j += sprintf(buf+j,"%c",',');

    if(obubsm.speed)
    j += sprintf(buf+j,"%.2f",obubsm.speed);
    j += sprintf(buf+j,"%c",',');

    if(obubsm.Heading)
    j += sprintf(buf+j,"%f",obubsm.Heading);
    j += sprintf(buf+j,"%c",',');

    if(obubsm.SteeringWheelAngle)
    j += sprintf(buf+j,"%f",obubsm.SteeringWheelAngle);
    j += sprintf(buf+j,"%c",',');

    if(obubsm.BrakeSystemStatus)
    j += sprintf(buf+j,"%d",obubsm.BrakeSystemStatus);
    j += sprintf(buf+j,"%c",',');

    if(obubsm.Acceleration)
    j += sprintf(buf+j,"%f",obubsm.Acceleration);
    j += sprintf(buf+j,"%c",',');
    /* 1-No turn signal
     * 2-right
     * 3-left
     * 4-hazard
     */
    if(obubsm.TurnSignal)
    j += sprintf(buf+j,"%c",obubsm.TurnSignal);
    int CCLength = 0;
    while(*buf && CCLength<200)
    {
        CCLength ++;
        buf++;
    }
    cout<<"CCLength"<<CCLength<<endl;
    buf -= CCLength;
    *(int8_t *)sbuf = static_cast<int8_t>(CCLength);
    for(int i = 0;i<CCLength;buf++,i++)
    {
        ++sbuf;
        *sbuf = *buf;
    }
//    cout<<"OBUPack success"<<endl;
}
