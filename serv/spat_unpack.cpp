#include "unpack.h"


struct TrafficLight spatunpack(char *buf)
{
    //cout<<"spat message unpacking"<<endl;
    TrafficLight light;
    light.mapId=(*(int8_t*)(buf));
    unsigned int i=0,list_num = *(int8_t*)(buf+1);
    while (i<list_num)
    {
        SpatMovementState spat;
        memset(&spat,0,sizeof(spat));
        spat.laneId=(*(int8_t*)(buf+2+16*i));
        spat.rightTimeToChange=(*(int8_t*)(buf+3+16*i));
        spat.straightTimeToChange=(*(int8_t*)(buf+4+16*i));
        spat.leftTimeToChange=(*(int8_t*)(buf+5+16*i));
        spat.rightState=(enum SpatLightState)(*(int8_t*)(buf+6+16*i));
        spat.straightState=(enum SpatLightState)(*(int8_t*)(buf+7+16*i));
        spat.leftState=(enum SpatLightState)(*(int8_t*)(buf+8+16*i));
        for(int m=0;m<3;m++)
             spat.rightTime[m]=(*(int8_t*)(buf+9+16*i+m));
        for(int m=0;m<3;m++)
             spat.straightTime[m]=(*(int8_t*)(buf+11+16*i+m));
        for(int m=0;m<3;m++)
             spat.leftTime[m]=(*(int8_t*)(buf+13+16*i+m));
        light.states.push_back(spat);
        i++;
    }
    return light;
}
