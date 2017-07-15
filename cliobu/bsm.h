#ifndef _BSM_H_
#define _BSM_H_

#include <vector>
#include <stdint.h>
#include "BasicSafetyMessage.h"

struct BsmBlob
{
    int    carId;
    double latitude;
    double longitude;
    double speed;
    double heading;
    double wheelAngle;
    bool   carBrake;
    double acceleration;
};

std::vector<uint8_t> BsmEncode(const BsmBlob &data);
BsmBlob BsmDecode(const std::vector<uint8_t> &data);

#endif
