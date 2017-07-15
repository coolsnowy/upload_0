#include "dataprocess.h"

char buf[500] = {0};
char frametype = '0';
void data_process(vector<uint8_t> vec,uint8_t *recvbuf,int recv_num)
{
    type_distinguish(recvbuf,vec,buf,frametype,recv_num);
}
void type_distinguish(uint8_t * recv_buf,vector<uint8_t> vec,char * buf,char &frametype,int recv_num)
{
    memset(buf,0,500);
    switch (recv_buf[5])
    {

    case 2:
    {
        Debug("BSM message\n");
        for(int i=0;i<recv_num;i++)
            printf("%02X ",recv_buf[i]);
        cout<<endl;
        BsmBlob bsmdata = BsmDecode(vec);
        RSUParticipant_upload(buf,bsmdata);
        RSUComm_upload(buf,bsmdata);
        frametype = 0x01;
        break;
    }
    {
        Debug("SPAT message\n");
        for(int i=0;i<recv_num;i++)
            printf("%02X ",recv_buf[i]);
        cout<<endl;
        TrafficLight spatdata = SpatDecode(vec);
        spat_upload(spatdata,buf);
        RSUComm_upload(buf,spatdata);
        frametype = 0x03;
        break;
    }
    case 07:
    {
        Debug("MAP message\n");
        for(int i=0;i<recv_num;i++)
            printf("%02X ",recv_buf[i]);
        cout<<endl;
        Map mapdata = MapDecode(vec);
        map_upload(mapdata,buf);
        RSUComm_upload(buf,mapdata);
        break;
    }
    }
    switch (recv_buf[4])
    {

    case 2:
    {
        Debug("BSM message\n");
        for(int i=0;i<recv_num;i++)
            printf("%02X ",recv_buf[i]);
        cout<<endl;
        BsmBlob bsmdata = BsmDecode(vec);
        RSUParticipant_upload(buf,bsmdata);
        RSUComm_upload(buf,bsmdata);
        frametype = 0x01;
        break;
    }
    case 13:
    {
        Debug("SPAT message\n");
        for(int i=0;i<recv_num;i++)
            printf("%02X ",recv_buf[i]);
        cout<<endl;
        TrafficLight spatdata = SpatDecode(vec);
        spat_upload(spatdata,buf);
        RSUComm_upload(buf,spatdata);
        frametype = 0x03;
        break;
    }
    case 07:
    {
        Debug("MAP message\n");
        for(int i=0;i<recv_num;i++)
            printf("%02X ",recv_buf[i]);
        cout<<endl;
        Map mapdata = MapDecode(vec);
        map_upload(mapdata,buf);
        RSUComm_upload(buf,mapdata);
        break;
    }
    }
}
