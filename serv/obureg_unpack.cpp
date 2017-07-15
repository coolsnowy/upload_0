#include "unpack.h"
struct OBURegisterdata OBUReg_unpack(char* recvbuf)
{
    struct OBURegisterdata OBURegdata;
    memset(&OBURegdata,0,sizeof(OBURegdata));
    char *str = recvbuf;
    char bu[100] = {0};
    memset(bu,0,100);
    int j = strlen(bu);
    //SeqNo
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    str += (j+1);
    strcpy(OBURegdata.SeqNo,bu);
    //VehType
    OBURegdata.VehType = *str;
    return OBURegdata;

}
