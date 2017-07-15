#ifndef DATA_H
#define DATA_H
struct Point
{
    long latitude;
    long longitude;
};

struct Lane
{
    Point laneCenter;
    long  laneId;
};

struct Mapdata
{
    int         mapId;      // Intersection id
    Point       mapCenter;  // Center point of intersection
    std::list<Lane> lanes;  // List of lanes
};

struct  OBURegisterdata
{
    char SeqNo[40] = {0};
    char VehType = '0';
};
struct OBUBSM
{
    int CCLength = 0;
    int MsgCnt = 0;
    struct timeval TimeStampMillisecond ;
    double Longtitude = 0;
    double Latitude = 0;
    double Elevation =0;
    double PositionAccuracy = 0;
    double speed = 0;
    double Heading = 0;
    double SteeringWheelAngle = 0;
    int BrakeSystemStatus = 0;
    double Acceleration = 0;
    char TurnSignal = '0';
};
struct OBUComm
{
    int CCLength = 0;
    struct timeval ReceiveTimeStampMillisecond;
    char CCType = 0;
    char MsgType = 0;
    int MsgCnt = 0;
    int HardwareSeqNo = 0;//from send device
};
struct  RSURegisterdata
{
    char SeqNo[40] = {0};
    char Name[20] = {0};
    char IPAddress[20] = {0};
    double Latitude = 0;
    double Longitude = 0;
    double Height = 0;
};
struct RSUParticipant
{
    char PTCLength;
    struct timeval TimeStampMillisecond;
    char PTCType = 0;
    char Source = 0;
    int PTCId = 0;
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
    char TurnSignal = '0';

};
struct RSUComm
{
    char CCLength;
    struct timeval ReceiveTimeStampMillisecond;
    char CCType = '0';
    char MsgType = '0';
    int MsgCnt = 0;
    int HardwareSeqNo = 0;

};
enum SpatLightState
{
    green  = 3,
    yellow = 2,
    red    = 1,
    error  = 4
};

struct SpatMovementState
{
    int laneId;
    int rightTimeToChange;
    int straightTimeToChange;
    int leftTimeToChange;
    SpatLightState rightState = error;
    SpatLightState straightState = error;
    SpatLightState leftState = error;
    int rightTime[3];  //green yellow red
    int straightTime[3];
    int leftTime[3];
};

struct TrafficLight
{
    int mapId;
    std::list<SpatMovementState> states;
};

#endif // DATA_H
