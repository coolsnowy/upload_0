#include "unpack.h"
struct Mapdata mapunpack(char *buf)
{
    // initial
    Mapdata mapmessage;
    mapmessage.mapId=0;
    memset(&mapmessage.mapCenter,0,sizeof(mapmessage.mapCenter));
//    list<Lane>::iterator it=mapmessage.lanes.begin();
//    while(it != mapmessage.lanes.end())
//    {
//        it->laneId=0;
//        it->laneCenter.latitude=0;
//        it->laneCenter.longitude=0;
//        it++;
//    }
    mapmessage.mapId = ntohs(*(int16_t*)(buf));
    mapmessage.mapCenter.latitude = ntohl(*(int32_t*)(buf+2));
    mapmessage.mapCenter.longitude = ntohl(*(int32_t*)(buf+6));
    unsigned int list_num = *(int8_t*)(buf+10);
    unsigned int i = 0;
    while(i<list_num)
    {
        struct Lane lane;
        lane.laneId=0;
        lane.laneCenter.latitude=0;
        lane.laneCenter.longitude=0;
        lane.laneId = *(int8_t*)(buf+11+9*i);
        lane.laneCenter.latitude = ntohl(*(int32_t*)(buf+12+9*i));
        lane.laneCenter.longitude = ntohl(*(int32_t*)(buf+16+9*i));
        mapmessage.lanes.push_back(lane);
        i++;
    }
    return mapmessage;
}
