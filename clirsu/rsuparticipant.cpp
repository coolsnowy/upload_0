#include "data.h"
extern char frametype;
void RSUParticipant_upload(char *buf,BsmBlob bsmdata)
{
    memset(buf,0,500);
    frametype = 0x44;
    struct RSUParticipant RSUPart_data = RSUParticipant_init( bsmdata);
    RSUParticipant_pack(buf,frametype,RSUPart_data);
    frame(frametype,buf);
}
struct RSUParticipant RSUParticipant_init(BsmBlob bsmdata)
{
    struct RSUParticipant RSUParticipantdata;
    memset(&RSUParticipantdata,0,sizeof(RSUParticipantdata));
    /* 0-unkmown 1-selfinfo 2-DRC 3-Video */
    RSUParticipantdata.PTCType = '2';
    /* 0-unknown 1-Motor 2-Non-Motor 3-Pedestrian 4-rsu */
    RSUParticipantdata.Source = '1';
    RSUParticipantdata.PTCId = bsmdata.carId;
    strcpy(RSUParticipantdata.HardwareSeqNo ,"ABC33546");
    RSUParticipantdata.Longitude = bsmdata.longitude;
    RSUParticipantdata.Latitude = bsmdata.latitude;
    RSUParticipantdata.Elevation = 0;
    RSUParticipantdata.PositionAccuracy = 0;
    RSUParticipantdata.Speed = bsmdata.speed;
    RSUParticipantdata.Heading = bsmdata.heading;
    RSUParticipantdata.SteeringWheelAngle  = bsmdata.wheelAngle;
    RSUParticipantdata.BrakeSystemStatus = bsmdata.carBrake;
    RSUParticipantdata.Acceleration = bsmdata.acceleration;
    /* 1-no turn signal 2 right 3 left 4 hazard signal*/
    RSUParticipantdata.TurnSignal = 1;
    return RSUParticipantdata;
}

void RSUParticipant_pack(char *sbuf,char &frametype,struct RSUParticipant RSUPartdata)
{
    frametype = 0x44;
    char *buf = new char [300];
    int j = 0;
    struct timeval tm;
    memset(&tm,0,sizeof(tm));
    gettimeofday(&tm,NULL);
    *(int32_t*)(buf+j) = htonl((int32_t)(tm.tv_sec));
    j += 4;
    *(int16_t*)(buf+j) = htons((int16_t)(tm.tv_usec));
    j += 2;
    if(RSUPartdata.PTCType)
        j += sprintf(buf+j,"%c",RSUPartdata.PTCType);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.Source)
        j += sprintf(buf+j,"%c",RSUPartdata.Source);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.PTCId)
        j += sprintf(buf+j,"%d",RSUPartdata.PTCId);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.HardwareSeqNo)
        j += sprintf(buf+j,"%s",RSUPartdata.HardwareSeqNo);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.Longitude)
        j += sprintf(buf+j,"%f",RSUPartdata.Longitude);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.Latitude)
        j += sprintf(buf+j,"%f",RSUPartdata.Latitude);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.Elevation)
        j += sprintf(buf+j,"%f",RSUPartdata.Elevation);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.PositionAccuracy)
        j += sprintf(buf+j,"%f",RSUPartdata.PositionAccuracy);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.Speed)
        j += sprintf(buf+j,"%f",RSUPartdata.Speed);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.Heading)
        j += sprintf(buf+j,"%f",RSUPartdata.Heading);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.SteeringWheelAngle)
        j += sprintf(buf+j,"%f",RSUPartdata.SteeringWheelAngle);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.BrakeSystemStatus)
        j += sprintf(buf+j,"%f",RSUPartdata.BrakeSystemStatus);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.Acceleration)
        j += sprintf(buf+j,"%f",RSUPartdata.Acceleration);
    j += sprintf(buf+j,"%c",',');
    if(RSUPartdata.TurnSignal)
        j += sprintf(buf+j,"%c",RSUPartdata.TurnSignal);

    int PTCLength = 0;
    while(*buf && PTCLength<300)
    {
        PTCLength ++;
        buf ++;
    }
    cout<<"PTCLength = "<<PTCLength<<endl;
    buf -= PTCLength;
    *(int8_t *)(sbuf) = static_cast<int8_t>(PTCLength);
    for(int i =0;i < PTCLength;buf++,i++)
    {
        ++sbuf;
        *sbuf = *buf;
    }

}
