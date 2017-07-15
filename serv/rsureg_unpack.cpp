#include "unpack.h"

struct RSURegisterdata RSURegunpack(char *recvbuf)
{
    struct RSURegisterdata RSURegdata;
    memset(&RSURegdata,0,sizeof(RSURegdata));
    char *str = recvbuf;
    char bu[100]={0};
    memset(bu,0,sizeof(bu));
    int j = strlen(bu);
    //SeqNo
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    strcpy(RSURegdata.SeqNo,bu);
    //cout<<j<<'\t'<<RSURegdata.SeqNo<<endl;
    //Name
    memset(bu,0,strlen(bu));
    str = str +j +1;
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    str += (j+1);
    strcpy(RSURegdata.Name,bu);
    //cout<<j<<'\t'<<RSURegdata.Name<<endl;
    //IPAddress
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    str += (j+1);
    strcpy(RSURegdata.IPAddress ,bu);
    //cout<<j<<'\t'<<RSURegdata.IPAddress<<endl;
    //Longitude
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    str += (j+1);
    RSURegdata.Longitude = atof(bu);
    //cout<<j<<'\t'<<RSURegdata.Longitude<<endl;
    //Latitude
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    str += (j+1);
    RSURegdata.Latitude = atof(bu);
    //cout<<j<<'\t'<<RSURegdata.Latitude<<endl;
    //Height
    memset(bu,0,strlen(bu));
    sscanf(str,"%[^,]",bu);
    j = strlen(bu);
    str += (j+1);
    RSURegdata.Height = atof(bu);
    //cout<<j<<'\t'<<RSURegdata.Height<<endl;

    return RSURegdata;

}
