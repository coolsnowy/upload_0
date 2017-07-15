#ifndef SPAT_H
#define SPAT_H

#include <vector>
#include <list>

#include "SPAT.h"

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

TrafficLight SpatDecode(const std::vector<uint8_t> &data);


void spat_pack(TrafficLight light, char *buf);
void spat_upload(TrafficLight spatdata,char *buf);


#endif // SPAT_H
