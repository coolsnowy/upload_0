#include "MapData.h"
#include "ApproachObject.h"
#include <iostream>
#include "mapdata.h"
using namespace std;
extern char frametype;
struct Map MapDecode(const std::vector<uint8_t> &data)
{
    Map result;

    MapData_t *map = nullptr;
    asn_dec_rval_t rval;
    rval = ::asn_DEF_MapData.ber_decoder(0, &::asn_DEF_MapData, (void **)&map, data.data(), data.size(), 0);
    if(rval.code != RC_OK) {
        cout<<"RC IS NOT OK"<<endl;
        ::asn_DEF_MapData.free_struct(&::asn_DEF_MapData, map, 0);
        return result;
    }

    // Assume one map message only contains one intersection information
    Intersection_t **inters     = map->intersections->list.array;
    Intersection_t  *inter      = nullptr;
    int              intercount = 1; //map->intersections->list.count;

    ApproachObject_t **lanes  = nullptr;
    ApproachObject_t  *lane   = nullptr;
    int                lanecount  = 0;

    Lane tmpLane;
    int id = -1;
    result.mapId = id;

    // iteration variable
    int i;
    int j;
// new version has add new message,ie.landwidth;!!
    for (i=0; i<intercount; i++) {
        inter = inters[i];
        result.mapId = ntohs(*reinterpret_cast<short *>(inter->id.buf)); //modifed !!!!!!!!!!!!!!!!!!!!!!!
        result.mapCenter.latitude= inter->refPoint->lat;
        result.mapCenter.longitude = inter ->refPoint->Long;
        lanes = inter->approaches.list.array;
        lanecount = inter->approaches.list.count;

        for (j=0; j<lanecount; j++) {
            lane = lanes[j];
            tmpLane.laneCenter.latitude  = lane->refPoint->lat;
            tmpLane.laneCenter.longitude = lane->refPoint->Long;
            tmpLane.laneId = *lane->approach->id;
            result.lanes.push_back(tmpLane);
        }
    }
    ::asn_DEF_MapData.free_struct(&::asn_DEF_MapData, map, 0);
    return result;
}

void map_upload(Map map , char *buf)
{
    //Debug("map_upload\n");
    memset(buf,0,500);
    frametype = 0x01;
    map_pack(map,buf);
    frame(frametype,buf);
}
void map_pack(Map &map,char *buf)
{
    //Debug("map_Pack\n");
    int j = 0;
    list<Lane>::size_type lane_num = 0,num = 0;
    lane_num= map.lanes.size();
    //Debug("lane_num = %d\n",lane_num);
    list<Lane>::iterator iter = map.lanes.begin();
    *(int16_t*)(buf+j) = htons((int16_t)(map.mapId));
    j += 2;
    *(int32_t*)(buf+j) = htonl((int32_t)(map.mapCenter.latitude));
    j += 4;
    *(int32_t*)(buf+j) = htonl((int32_t)(map.mapCenter.longitude));
    j += 4;
    *(int8_t*)(buf+j) = static_cast<int8_t> (lane_num);
    j += 1;
    while(num<lane_num)//4 * 9 + 11 = 47
    {
        *(int8_t*)(buf+j) = static_cast<int8_t> (iter->laneId);
        j += 1;
        *(int32_t*)(buf+j) = htonl((int32_t)(iter->laneCenter.latitude));
        j += 4;
        *(int32_t*)(buf+j) = htonl((int32_t)(iter->laneCenter.longitude));
        j += 4;
        iter++;
        num++;
    }
}
