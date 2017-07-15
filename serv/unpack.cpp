#include "unpack.h"
#include <fstream>
#include "stdio.h"
#include "data.h"
#include "sys/time.h"
#include "tcpserv.h"
#include "log.h"
extern const char *filename;
unsigned char CRC(char *puchMsg,int16_t count)
{
    //generate CRC inquiry table
    unsigned char CRC=0x00;
    unsigned char bit;
    int i;
     char *cp;
    puchMsg[count] = 0x00;                   //在末尾添加8个0
    cp = puchMsg;
    CRC = *cp;
    cp = cp+1;
    bit = (CRC>>7)   &   0x01;       //记录最高位
    CRC = (CRC<<1)|(*cp>>7);
    while (count--)
    {
        for (i=0;i<8;i++)
        {
            if (bit   !=   0)
            CRC = CRC^0x07;                 //生成多项式为107H
            bit = (CRC>>7)&0x01;
            if(i==7)
            {
                cp++;
                CRC = (CRC<<1)|(*cp>>7);
            }
            else
                CRC = (CRC<<1)|((*cp&(char)pow(2,6-i))>>(6-i));     //pow()为求方函数
        }
        i = 0;
    }
    CRC = ((CRC>>1)|(bit<<7))^0xff;           //陪集码为0xff
    return CRC;
}
void type_distinguish(char *data_head,char *recvbuf,int sock_fd,int len_not_include_crc)
{
    ofstream in;
    in.open(filename,ios::out|ios::app);
    Debug("start type distinguish\n");
    in<<"start type distinguish"<<endl;

    if (*data_head == 0x59 && *(data_head + 1) == 0x5A)
    {
        //debug
        //        for(int i=0;i<6;i++)
        //            printf("%02hhX ",data_head[i]);
        //        for(int i=0;i<18;i++)
        //            printf("%02hhX ",recvbuf[i]);
//        char tmpbuf[300] = {0};
//        for(int i=0;i<len_not_include_crc;i++)
//        {
//            if(i<6)
//                tmpbuf[i] = data_head[i];
//            else if(i>=6)
//                tmpbuf[i] = recvbuf[i-6];
//            //printf("%02hhX ",tmpbuf[i]);
//        }
//        unsigned a = CRC(tmpbuf,21);
//        int8_t tmpcrc = static_cast<int8_t>(a);
//        cout<<endl;
        //Debug("head right = 595A\n");
        in<<"head right = 595A"<<endl;
/************************************************************/
//        SPAT message
        if (*(data_head + 3) == 0x02)
        {
            Debug("  SPAT DATA\n\n");
            struct TrafficLight spatmessage = spatunpack(recvbuf);
            cout << "mapId :" << spatmessage.mapId << endl;
            list<SpatMovementState>::iterator iter = spatmessage.states.begin();
            for (int num = 0; iter != spatmessage.states.end(); num++, iter++)
            {
                cout<<endl;
                cout << "spat [" << num + 1 << "]:" << endl;
                cout << "laneId:" << iter->laneId << endl;
                cout << "right time to change :" << iter->rightTimeToChange
                        << endl;
                cout << "straight time to change :"
                        << iter->straightTimeToChange << endl;
                cout << "left time to change : " << iter->leftTimeToChange
                        << endl;
                cout << "right state: " << iter->rightState << endl;
                cout << "straight state: " << iter->straightState << endl;
                cout << "left state: " << iter->leftState << endl;
                cout << "right time:" << "greed: " << iter->rightTime[0]
                        << " yellow:" << iter->rightTime[1] << " red:"
                        << iter->rightTime[2] << endl;
                cout << "straight time:" << "greed: " << iter->straightTime[0]
                        << " yellow:" << iter->straightTime[1] << " red:"
                        << iter->straightTime[2] << endl;
                cout << "left time:" << "greed: " << iter->leftTime[0]
                        << " yellow:" << iter->leftTime[1] << " red:"
                        << iter->leftTime[2] << endl;
            }
        }
//        map data
        if(*(data_head + 3) == 0x01)
        {
            struct Mapdata mapdata;
            Debug("  MAP DATA\n");
            mapdata = mapunpack(recvbuf);
            cout << "mapId:" << mapdata.mapId << endl;
            cout << "mapcenter gps :latitude  :"
                    << mapdata.mapCenter.latitude << "  longitude:  "
                    << mapdata.mapCenter.longitude << endl;
            list<Lane>::iterator map_iter = mapdata.lanes.begin();
            for (int num = 0; map_iter != mapdata.lanes.end(); num++, map_iter++)
            {
                cout << "laneId[" << num + 1 << "]:" << map_iter->laneId << endl;
                cout << "lanecenter [" << num + 1 << "]: latitude "
                        << map_iter->laneCenter.latitude;
                cout << "  longitude:  " << map_iter->laneCenter.longitude << endl;
            }
        }

//        OBU register
        if(*(data_head + 3) == 0x21)
        {
            Debug("  OBUREGISTER DATA\n\n");
            char *returnbuf = new char [10];
            struct OBURegisterdata OBURegdata;
            memset(&OBURegdata,0,sizeof(OBURegdata));
            OBURegdata = OBUReg_unpack(recvbuf);
            cout<<"SeqNo = "<<OBURegdata.SeqNo<<endl;
            cout<<"VehType = "<<OBURegdata.VehType<<endl;

            // assume ok
            int OBUreturnlen =0;
            if(1)
            {
                *returnbuf = 'o';
                *(returnbuf+1) = 'k';
                *(returnbuf+2) = '\0';
                //without considering error
                while(*returnbuf && OBUreturnlen <9)
                {
                    OBUreturnlen ++;
                    returnbuf ++;
                }
                cout<<"OBUreturnlen="<<OBUreturnlen<<endl;
                returnbuf -= OBUreturnlen;
                cout<<"return content: "<<returnbuf<<endl;
             }
            else if(0)
            {
                *returnbuf = 'e';
                *(returnbuf+1) = 'r';
                *(returnbuf+2) = 'r';
                //without considering error
                while(*returnbuf && OBUreturnlen <9)
                {
                    OBUreturnlen ++;
                    returnbuf ++;
                }
                cout<<"OBUreturnlen="<<OBUreturnlen<<endl;
                returnbuf -= OBUreturnlen;
                cout<<"return content: "<<returnbuf<<endl;

            }
            int send_num;
            send_num = send(sock_fd, returnbuf,OBUreturnlen, 0);
            if (send_num < 0)
            {
                perror("server send error:");
                exit(1);
             }
             else
                cout<<"server send success"<<endl;
            cout<<"*************************************************************************"<<endl;
        }
//        OBU Bsm
        if(*(data_head + 3) == 0x22)
        {
            Debug("  OBUBSM DATA\n\n");
            struct OBUBSM bsmdata ;
            memset(&bsmdata,0,sizeof(bsmdata));
            bsmdata = bsmunpack(recvbuf);
            cout<<"OBUBSM data length = "<<bsmdata.CCLength<<endl;
            cout<<"OBUBSM MsgCnt = "<<bsmdata.MsgCnt<<endl;
            cout<<"OBUBSM TimeStamp Millisecond = "<<bsmdata.TimeStampMillisecond.tv_sec*1000+bsmdata.TimeStampMillisecond.tv_usec/1000 <<endl;
            //show time
            cout<<bsmdata.TimeStampMillisecond.tv_sec<<'\t'<<bsmdata.TimeStampMillisecond.tv_usec<<endl;
            cout<<"transfer to time clock :";
            char tbuf[100] = {0};
            char tmbuf[100] = {0};
            time_t nowtime;
            struct tm *nowtm;
            struct timeval tv;
            tv.tv_sec = bsmdata.TimeStampMillisecond.tv_sec ;
            tv.tv_usec = bsmdata.TimeStampMillisecond.tv_usec;
            nowtime = tv.tv_sec; //nowtime storge the sec_time
            nowtm = localtime(&nowtime); //transfer nowtime to time_struct
            //use strftime to transfer tv to string,but the precision can only achieive sec
            strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
            //add ms to the previous string
            snprintf(tbuf, sizeof tbuf, "%s.%06ld", tmbuf, tv.tv_usec);
            cout<<tbuf<<endl;

            cout<<"OBUBSM Longtitude = "<<bsmdata.Longtitude<<endl;
            cout<<"OBUBSM Latitude = "<<bsmdata.Latitude<<endl;
            cout<<"OBUBSM Elevation = "<<bsmdata.Elevation<<endl;
            cout<<"OBUBSM PositionAccuracy = "<<bsmdata.PositionAccuracy<<endl;
            cout<<"OBUBSM Speed = "<<bsmdata.speed<<endl;
            cout<<"OBUBSM Heading = "<<bsmdata.Heading<<endl;
            cout<<"OBUBSM SteeringWheelAngle = "<<bsmdata.SteeringWheelAngle<<endl;
            cout<<"OBUBSM BrakeSystemStatus = "<<bsmdata.BrakeSystemStatus<<endl;
            cout<<"OBUBSM Acceleration = "<<bsmdata.Acceleration<<endl;
            cout<<"OBUBSM TurnSingal = "<<bsmdata.TurnSignal<<endl;
            cout<<"*************************************************************************"<<endl;
        }
//        OBU Comm
        if(*(data_head + 3) == 0x24)
        {
            Debug("  OBUCOMM DATA\n\n");
            struct OBUComm OBUCommdata;
            memset(&OBUCommdata,0,sizeof(OBUCommdata));
            OBUCommdata = OBUCommunpack(recvbuf);
            cout<<"OBUComm data length = "<<OBUCommdata.CCLength<<endl;
            cout<<"OBUComm TimeStamp Millisecond = "<<OBUCommdata.ReceiveTimeStampMillisecond.tv_sec*1000 +OBUCommdata.ReceiveTimeStampMillisecond.tv_usec/1000 <<endl;
            //showtime
            cout<<OBUCommdata.ReceiveTimeStampMillisecond.tv_sec<<'\t'<<OBUCommdata.ReceiveTimeStampMillisecond.tv_usec<<endl;
            cout<<"transfer to time clock :";
            char tbuf[100] = {0};
            char tmbuf[100] = {0};
            time_t nowtime;
            struct tm *nowtm;
            struct timeval tv;
            tv.tv_sec = OBUCommdata.ReceiveTimeStampMillisecond.tv_sec;
            tv.tv_usec = OBUCommdata.ReceiveTimeStampMillisecond.tv_usec;
            nowtime = tv.tv_sec; //nowtime storge the sec_time
            nowtm = localtime(&nowtime); //transfer nowtime to time_struct
            //use strftime to transfer tv to string,but the precision can only achieive sec
            strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
            //add ms to the previous string
            snprintf(tbuf, sizeof tbuf, "%s.%06ld", tmbuf, tv.tv_usec);
            cout<<tbuf<<endl;
            cout<<"OBUComm CCType = "<<OBUCommdata.CCType<<endl;
            cout<<"OBUComm MsgType = "<<OBUCommdata.MsgType<<endl;
            cout<<"OBUComm MsgCnt = "<<OBUCommdata.MsgCnt<<endl;
            cout<<"OBUComm HardwareSeqNo = "<<OBUCommdata.HardwareSeqNo<<endl;
            cout<<"*************************************************************************"<<endl;
        }
//        RSU Register
        if(*(data_head + 3) == 0x41)
        {
            Debug("  RSUREGISTER DATA\n\n");
            char *returnbuf = new char [10];
            struct RSURegisterdata RSURegdata;
            memset(&RSURegdata,0,sizeof(RSURegdata));
            RSURegdata = RSURegunpack(recvbuf);
            //show useful message
            cout<<"SeqNo = "<<RSURegdata.SeqNo<<endl;
            cout<<"Name = "<<RSURegdata.Name<<endl;
            cout<<"IPAddress = "<<RSURegdata.IPAddress<<endl;
            cout<<"Longitude = "<<RSURegdata.Longitude<<endl;
            cout<<"Latitude = "<<RSURegdata.Latitude<<endl;
            cout<<"Height = "<<RSURegdata.Height<<endl;
            int OBUreturnlen =0;
            if(1)
            {
                *returnbuf = 'o';
                *(returnbuf+1) = 'k';
                *(returnbuf+2) = '\0';
                //without considering error
                while(*returnbuf && OBUreturnlen <9)
                {
                    OBUreturnlen ++;
                    returnbuf ++;
                }
                cout<<"OBUreturnlen="<<OBUreturnlen<<endl;
                returnbuf -= OBUreturnlen;
                cout<<"return content: "<<returnbuf<<endl;
             }
            else if(0)
            {
                *returnbuf = 'e';
                *(returnbuf+1) = 'r';
                *(returnbuf+2) = 'r';
                //without considering error
                while(*returnbuf && OBUreturnlen <9)
                {
                    OBUreturnlen ++;
                    returnbuf ++;
                }
                cout<<"OBUreturnlen="<<OBUreturnlen<<endl;
                returnbuf -= OBUreturnlen;
                cout<<"return content: "<<returnbuf<<endl;

            }
            int send_num;
            send_num = send(sock_fd, returnbuf,OBUreturnlen, 0);
            if (send_num < 0)
            {
                perror("server send error:");
                exit(1);
             }
             else
                cout<<"server send success"<<endl;
            cout<<"*************************************************************************"<<endl;

        }
//        RSUParticipant
        if(*(data_head+3) == 0x44)
        {
            Debug("  RSUPARTICIPANT DATA\n\n");
            struct RSUParticipant RSUPartdata;
            memset(&RSUPartdata,0,sizeof(RSUPartdata));
            RSUPartdata = RSUPartunpack(recvbuf);
            cout<<"length of data followed = "<<(int)RSUPartdata.PTCLength<<endl;
            cout<<"RSUParticipant Time Stamp Miiliseconf = "<<RSUPartdata.TimeStampMillisecond.tv_sec*1000+RSUPartdata.TimeStampMillisecond.tv_usec/1000<<endl;
            char tbuf[100] = {0};
            char tmbuf[100] = {0};
            time_t nowtime;
            struct tm *nowtm;
            struct timeval tv;
            tv.tv_sec = RSUPartdata.TimeStampMillisecond.tv_sec;
            tv.tv_usec = RSUPartdata.TimeStampMillisecond.tv_usec;
            nowtime = tv.tv_sec; //nowtime storge the sec_time
            nowtm = localtime(&nowtime); //transfer nowtime to time_struct
            //use strftime to transfer tv to string,but the precision can only achieive sec
            strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
            //add ms to the previous string
            snprintf(tbuf, sizeof tbuf, "%s.%06ld", tmbuf, tv.tv_usec);
            cout<<tbuf<<endl;
            cout<<"type 0f Participant = "<<(int)RSUPartdata.PTCType<<endl;
            cout<<"type 0f detecte = "<<(int)RSUPartdata.Source<<endl;
            cout<<"Participant Id = "<<RSUPartdata.PTCId<<endl;
            cout<<"Participant Hardware = "<<RSUPartdata.HardwareSeqNo<<endl;
            cout<<"Participant Longitude = "<<RSUPartdata.Longitude<<endl;
            cout<<"Participant Latitude = "<<RSUPartdata.Latitude<<endl;
            cout<<"Participant Elevation = "<<RSUPartdata.Elevation<<endl;
            cout<<"Participant PositionAccuracy = "<<RSUPartdata.PositionAccuracy<<endl;
            cout<<"Participant Speed = "<<RSUPartdata.Speed<<endl;
            cout<<"Participant Heading = "<<RSUPartdata.Heading<<endl;
            cout<<"Participant SteeringWheel Angle = "<<RSUPartdata.SteeringWheelAngle<<endl;
            cout<<"Participant Brake = "<<RSUPartdata.BrakeSystemStatus<<endl;
            cout<<"Participant Acceleration = "<<RSUPartdata.Acceleration<<endl;
            cout<<"Participant Turnsignal = "<<RSUPartdata.TurnSignal<<endl;
            cout<<"/********************************************************************"<<endl;

        }
//        RSU Comm
        if(*(data_head + 3) == 0x45)
        {
            Debug("  RSUCOMM DATA\n\n");
            struct RSUComm RSUCommdata;
            memset(&RSUCommdata,0,sizeof(RSUCommdata));
            RSUCommdata = RSUCommunpack(recvbuf);
            cout<<"RSUComm data length = "<<(unsigned int)RSUCommdata.CCLength<<endl;
            cout<<"RSUComm TimeStamp Millisecond = "<<RSUCommdata.ReceiveTimeStampMillisecond.tv_sec*1000 +RSUCommdata.ReceiveTimeStampMillisecond.tv_usec/1000 <<endl;
            //showtime
            cout<<RSUCommdata.ReceiveTimeStampMillisecond.tv_sec<<'\t'<<RSUCommdata.ReceiveTimeStampMillisecond.tv_usec<<endl;
            cout<<"transfer to time clock :";
            char tbuf[100] = {0};
            char tmbuf[100] = {0};
            time_t nowtime;
            struct tm *nowtm;
            struct timeval tv;
            tv.tv_sec = RSUCommdata.ReceiveTimeStampMillisecond.tv_sec;
            tv.tv_usec = RSUCommdata.ReceiveTimeStampMillisecond.tv_usec;
            nowtime = tv.tv_sec; //nowtime storge the sec_time
            nowtm = localtime(&nowtime); //transfer nowtime to time_struct
            //use strftime to transfer tv to string,but the precision can only achieive sec
            strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
            //add ms to the previous string
            snprintf(tbuf, sizeof tbuf, "%s.%06ld", tmbuf, tv.tv_usec);
            cout<<tbuf<<endl;
            cout<<"RSUComm CCType = "<<RSUCommdata.CCType<<endl;
            cout<<"RSUComm MsgType = "<<RSUCommdata.MsgType<<endl;
            cout<<"RSUComm MsgCnt = "<<RSUCommdata.MsgCnt<<endl;
            cout<<"RSUComm HardwareSeqNo = "<<RSUCommdata.HardwareSeqNo<<endl;
            cout<<"*************************************************************************"<<endl;
        }

    }
}


