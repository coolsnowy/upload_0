#include "unpack.h"

struct RSUParticipant RSUPartunpack(char *recvbuf)
{
    struct RSUParticipant RSUPartdata;
    memset(&RSUPartdata,0,sizeof(RSUPartdata));
    RSUPartdata.PTCLength = *(int8_t*)(recvbuf);
    RSUPartdata.TimeStampMillisecond.tv_sec = ntohl(*(int32_t*)(recvbuf+1));
    RSUPartdata.TimeStampMillisecond.tv_usec = ntohs(*(int16_t*)(recvbuf+5));
    RSUPartdata.PTCType = *(int8_t*)(recvbuf+7);
    RSUPartdata.Source = *(int8_t*)(recvbuf+9);//consider ','
    char *str = recvbuf+11;
    int j = 0;
    char bu[100] = {0};

    //PTCId
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<"j = "<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.PTCId = atof(bu);
    //HardwareSeqNo
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<j<<bu<<endl;
    str += (j+1);
    strcpy(RSUPartdata.HardwareSeqNo,bu);
    // Longitude
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    //cout<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.Longitude = atof(bu);
    //Latitude
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.Latitude = atof(bu);
    //Elevation
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.Elevation = atof(bu);
    //PositionAccuracy
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.PositionAccuracy= atof(bu);
    //speed
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    str += (j+1);
    RSUPartdata.Speed= atof(bu);

    //Heading
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.Heading= atof(bu);
    //SteeringWheelAngle
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.SteeringWheelAngle= atof(bu);
    //BrakeSysemStatus
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    cout<<j<<bu<<endl;
    str += (j+1);
    RSUPartdata.BrakeSystemStatus= atoi(bu);
    //Acceleration
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j=strlen(bu);
    //cout<<j;cout<<bu<<endl;
    str += (j+1);
    RSUPartdata.Acceleration= atof(bu);
    //TurnSignal
    memset(bu,0,strlen(bu));
    sscanf(str,"%s",bu);
    j=strlen(bu);
    //cout<<"j = "<<j<<endl;
    //cout<<"buf: "<<bu<<endl;
    RSUPartdata.TurnSignal = atoi(bu);
    //cout<<RSUPartdata.TurnSignal<<endl;
    return RSUPartdata;

}
