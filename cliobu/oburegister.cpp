#include "data.h"
extern char frametype;
extern tcp_client tcpcli;
extern const char *filepath;
struct OBURegisterdata OBURegist_init(const char *filepath)
{
    Json::Reader reader ;
    Json::Value root;
    ifstream in;
    in.open(filepath,ios::binary);
    const char *SeqNo  = 0;
    const char *VehType = 0;

    if(!in.is_open())
    {
        Debug("Error opening file\n");
        exit(0);
    }
    if(reader.parse(in,root))
    {
        string s1 = root["OBUSeqNo"].asString();
        SeqNo = s1.c_str();

        string s2 = root["VehType"].asString();
        VehType = s2.c_str();
    }
    struct OBURegisterdata OBURegdata;

    memset(&OBURegdata,0,sizeof(OBURegdata));
    char *p = (char *)SeqNo;
    int i = 0;
    while(*p)
    {
        OBURegdata.SeqNo[i] = *p;
        p++;
        i++;
    }
    p = (char*) VehType;
    i = 0;
    OBURegdata.VehType = *p;

    return OBURegdata;
}
void OBURegister(char *buf,char &frametype,struct OBURegisterdata OBURegdata )
{
    cout<<"start OBURegister Pack"<<endl;
    frametype = 0x21;//OBURegister
    int j = 0;
    if(OBURegdata.SeqNo)
        j += sprintf(buf+j,"%s",OBURegdata.SeqNo);
    j += sprintf(buf+j,"%c",',');
    if(OBURegdata.VehType)
        j += sprintf(buf+j,"%c",OBURegdata.VehType);

}
void OBURegister_upload(char *buf)
{
    memset(buf,0,500);
    struct OBURegisterdata OBUReg_data = OBURegist_init(filepath);
    frametype = 0x41;
    OBURegister(buf,frametype,OBUReg_data);
    frame(frametype,buf);
    OBURegist_ok();
}
void OBURegist_ok()
{
    char *OBUreturnbuf = new char[100];
    tcpcli.recv_data(OBUreturnbuf);
    if(*OBUreturnbuf == 'o' && *(OBUreturnbuf+1) =='k')
    {
        Debug("register ok\n");
    }
    else
    {
        Debug("register failure,procedure exit!\n");
        exit(0);
    }
    delete []OBUreturnbuf;
}
