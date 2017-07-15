#include "unpack.h"
struct OBUBSM bsmunpack(char *recvbuf)
{
    struct OBUBSM bsmdata;
    memset(&bsmdata,0,sizeof(bsmdata));
    bsmdata.CCLength = *(int8_t*)(recvbuf);
    bsmdata.MsgCnt = *(int8_t*)(recvbuf+1);
    bsmdata.TimeStampMillisecond.tv_sec = ntohl(*(int32_t*)(recvbuf+2));
    bsmdata.TimeStampMillisecond.tv_usec = ntohs(*(int16_t*)(recvbuf+6));
    char *str = recvbuf+8;
    char bu[100] = {0};
    int j = strlen(bu);
    // Longitude
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    str = str+j+1;
    bsmdata.Longtitude = atof(bu);
    //Latitude
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    //cout<<"latitude bu"<<bu<<endl;
    bsmdata.Latitude = atof(bu);
    //cout<<"bsmdata.Latitude "<<bsmdata.Latitude<<endl;
    //Elevation
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    bsmdata.Elevation = atof(bu);
    //PositionAccuracy
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    bsmdata.PositionAccuracy= atof(bu);
    //speed
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    bsmdata.speed= atof(bu);
    //Heading
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    bsmdata.Heading= atof(bu);
    //SteeringWheelAngle
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    bsmdata.SteeringWheelAngle= atof(bu);
    //BrakeSysemStatus
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    bsmdata.BrakeSystemStatus= atoi(bu);
    //Acceleration
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    bsmdata.Acceleration= atof(bu);
    //TurnSignal
    memset(bu,0,strlen(bu));
    sscanf(str,"%s",bu);
    j=strlen(bu);
    bsmdata.TurnSignal = atoi(bu);
    return bsmdata;
}
