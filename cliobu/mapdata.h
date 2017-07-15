#ifndef _MAPDATA_H_
#define _MAPDATA_H_

#include <vector>
#include <list>
#include "dataprocess.h"
#include <stdint.h>

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

struct Map
{
    int         mapId;      // Intersection id
    Point       mapCenter;  // Center point of intersection
    std::list<Lane> lanes;  // List of lanes
};

Map MapDecode(const std::vector<uint8_t> &data);
void map_upload(Map map, char *buf);
void map_pack(Map &map, char *buf);
#endif
