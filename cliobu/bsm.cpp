#include "bsm.h"
#include<iostream>
using namespace std;

std::vector<uint8_t> BsmEncode(const BsmBlob &data)
{
    int32_t carId = data.carId;
    int32_t latitude  = static_cast<int32_t>(data.latitude*10000000);
    int32_t longitude = static_cast<int32_t>(data.longitude*10000000);
    int16_t speed     = static_cast<int16_t>(data.speed/3.6*50);
    int16_t heading   = static_cast<int16_t>(data.heading/0.0125);
    int32_t wheelAngle   = static_cast<int32_t>(data.wheelAngle/1.5);
    int16_t acceleration = static_cast<int16_t>(data.acceleration*100);

    char buf[38] = {0};

    // id (1~4)
    *reinterpret_cast<int32_t *>(buf+1) = htonl(carId);

    // lat (7~10)
    // range: -900000000 ~ 900000000, unavailable:900000001
    if(latitude>900000000 || latitude < -900000000) {
        latitude = 900000001;
    }
    *reinterpret_cast<int32_t *>(buf+7) = htonl(latitude);

    // long (11~14)
    // range: -1800000000 ~ 1800000000, unavailable:1800000001
    if(longitude>1800000000 || longitude<-1800000000) {
        longitude = 1800000001;
    }
    *reinterpret_cast<int32_t *>(buf+11) = htonl(longitude);

    // speed (21~22)
    // range: 0 ~ 8192
    *reinterpret_cast<int16_t *>(buf+21) = htons(speed);

    // heading (23~24)
    // range:0 ~ 28799, unavailable:28800
    if(heading<0 || heading>28799) {
        heading = 28800;
    }
    *reinterpret_cast<int16_t *>(buf+23) = htons(heading);

    // angle (25)
    // range: -126 ~ 126, unavailable:127
    if(wheelAngle<-126 || wheelAngle>126) {
        wheelAngle = 127;
    }
    buf[25] = wheelAngle & 0xFF;

    // acce(26~27)
    if(acceleration<0 || acceleration>5000) {
        acceleration = -1;
    }
    *reinterpret_cast<int16_t *>(buf+26) = htons(acceleration);

    struct BasicSafetyMessage *bsm = reinterpret_cast<BasicSafetyMessage *>(::calloc(1, sizeof(struct BasicSafetyMessage)));
    bsm->msgID = DSRCmsgID::DSRCmsgID_basicSafetyMessage;
    ::OCTET_STRING_fromBuf(&bsm->blob1, buf, sizeof(buf));

    /*if(carBrake)
    {
        bsmmessage->safetyExt = (VehicleSafetyExtension*)CALLOC(1,sizeof(VehicleSafetyExtension));
        bsmmessage->safetyExt->events = (EventFlags_t*)CALLOC(1,sizeof(EventFlags_t));
        *(bsmmessage->safetyExt->events) = 128;
    }*/

    // Encode
    char message[1024];
    asn_enc_rval_t er;
    er = ::der_encode_to_buffer(&::asn_DEF_BasicSafetyMessage, bsm, message, sizeof(message));
    ::asn_DEF_BasicSafetyMessage.free_struct(&::asn_DEF_BasicSafetyMessage, bsm, 0);

    if(er.encoded != -1) {
        return std::vector<uint8_t>(message, message+er.encoded);
    }else {
        return std::vector<uint8_t>();
    }
}

BsmBlob BsmDecode(const std::vector<uint8_t> &data)
{
    cout<<"BSM Decode\n";
    struct BasicSafetyMessage *bsm = NULL;
    asn_dec_rval_t rval;
    rval = ::asn_DEF_BasicSafetyMessage.ber_decoder(0, &::asn_DEF_BasicSafetyMessage,
            reinterpret_cast<void **>(&bsm), data.data(), data.size(), 0);

    BsmBlob blob;
    if(rval.code == RC_OK) {
        cout<<"crc_ok"<<endl;
        int32_t carId;
        int32_t latitude;
        int32_t longitude;
        int32_t speed;
        int32_t heading;
        int32_t acceleration;
        int32_t wheelAngle;

        // id (1 - 4)
        carId = ntohl(*reinterpret_cast<int32_t *>(bsm->blob1.buf+1));
        cout<<"carid="<<carId<<endl;
        // lat (7 - 10)
        latitude = ntohl(*reinterpret_cast<int32_t *>(bsm->blob1.buf+7));
        cout<<"latitude="<<latitude<<endl;
        // long (11 - 14)
        longitude = ntohl(*reinterpret_cast<int32_t *>(bsm->blob1.buf+11));
        cout<<"longitude="<<longitude<<endl;
        // speed (21 - 22)
        speed = ntohs(*reinterpret_cast<int16_t *>(bsm->blob1.buf+21));
        cout<<"speed="<<speed<<endl;
        // heading (23 - 24)
        heading = ntohs(*reinterpret_cast<int16_t *>(bsm->blob1.buf+23));
        cout<<"heading="<<heading<<endl;
        // angle (25)
        wheelAngle = bsm->blob1.buf[25];
        cout<<"wheelangle="<<wheelAngle<<endl;
        // acceleration (26 - 27)
        acceleration = ntohs(*reinterpret_cast<int16_t *>(bsm->blob1.buf+26));
        cout<<"acceleraion="<<acceleration<<endl;
        // safetyEvent:Brake
        /*if(bsm->safetyExt !=NULL && bsm->safetyExt->events!=NULL && *(bsmmsg->safetyExt->events) == 128)
        {
            blob.carBrake = true;
        }*/
        cout<<"1"<<endl;
        blob.carId        = carId;
        cout<<"blob.carId="<<blob.carId<<endl;
        blob.latitude     = latitude/10000000.0;
        blob.longitude    = longitude/10000000.0;
        blob.speed        = speed/50.0*3.6;
        blob.heading      = heading*0.0125;
        blob.wheelAngle   = wheelAngle*1.5;
        blob.acceleration = acceleration/100.0;
        cout<<"blob.speed="<<blob.speed<<endl;

    }

    ::asn_DEF_BasicSafetyMessage.free_struct(&::asn_DEF_BasicSafetyMessage, bsm, 0);
    cout<<"BSM Decode success\n";
    return blob;
}
