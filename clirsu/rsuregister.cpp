#include "data.h"
extern char frametype;
extern tcp_client tcpcli;
extern const char *filepath;
struct RSURegisterdata RSURegist_init(const char *filepath)
{
    Json::Reader reader ;
    Json::Value root;
    ifstream in;
    in.open(filepath,ios::binary);
    const char *SeqNo  = 0;
    const char *Name = 0;
    const char *IpAddress = 0;
    double Latitude = 0;
    double Longitude = 0;
    double Height = 0;
    if(!in.is_open())
    {
        Debug("Error opening file\n");
        exit(0);
    }
    if(reader.parse(in,root))
    {
        string s1 = root["SeqNo"].asString();
        SeqNo = s1.c_str();

        string s2 = root["Name"].asString();
        Name = s2.c_str();

        string s3 = root["IpAddress"].asString();
        IpAddress = s3.c_str();

        string s4 = root["Latitude"].asString();
        Latitude = atof(s4.c_str());

        string s5 = root["Longitude"].asString();
        Longitude = atof(s5.c_str());

        string s6 = root["Height"].asString();
        Height = atof(s6.c_str());
    }
    struct RSURegisterdata RSURegdata;

    memset(&RSURegdata,0,sizeof(RSURegdata));
    char *p = (char *)SeqNo;
    int i = 0;
    while(*p)
    {

        RSURegdata.SeqNo[i] = *p;
        p++;
        i++;
    }
    p = (char*) Name;
    i = 0;
    while(*p)
    {

        RSURegdata.Name[i] = *p;
        p++;
        i++;
    }
    p = (char *)IpAddress;
    i = 0;
    while(*p)
    {

        RSURegdata.IpAddress[i] = *p;
        p++;
        i++;
    }
    RSURegdata.Latitude = Latitude;
    RSURegdata.Longitude = Longitude;
    RSURegdata.Height = Height;

    return RSURegdata;
}
void RSURegister(char *buf,char &frametype,struct RSURegisterdata RSURegdata )
{
    cout<<"start RSURegister Pack"<<endl;
    frametype = 0x41;//RSURegister
    int j = 0;
    if(RSURegdata.SeqNo)
        j += sprintf(buf+j,"%s",RSURegdata.SeqNo);
    j += sprintf(buf+j,"%c",',');
    if(RSURegdata.Name)
        j += sprintf(buf+j,"%s",RSURegdata.Name);
    j += sprintf(buf+j,"%c",',');
    if(RSURegdata.IpAddress)
        j += sprintf(buf+j,"%s",RSURegdata.IpAddress);
    j += sprintf(buf+j,"%c",',');

    if(RSURegdata.Longitude)
        j += sprintf(buf+j,"%f",RSURegdata.Longitude);
    j += sprintf(buf+j,"%c",',');
    if(RSURegdata.Latitude)
        j += sprintf(buf+j,"%f",RSURegdata.Latitude);
    j += sprintf(buf+j,"%c",',');
    if(RSURegdata.Height)
        j += sprintf(buf+j,"%f",RSURegdata.Height);
    j += sprintf(buf+j,"%c",',');
    cout<<"RSURegister Pack success"<<endl;
}
void RSURegister_upload(char *buf)
{
    memset(buf,0,500);
    struct RSURegisterdata RSUReg_data = RSURegist_init(filepath);
    frametype = 0x41;
    RSURegister(buf,frametype,RSUReg_data);
    frame(frametype,buf);
    RSURegist_ok();
}
void RSURegist_ok()
{
    char *RSUreturnbuf = new char[100];
    tcpcli.recv_data(RSUreturnbuf);
    if(*RSUreturnbuf == 'o' && *(RSUreturnbuf+1) =='k')
    {
        Debug("register ok\n");
    }
    else
    {
        Debug("register failure,procedure exit!\n");
        exit(0);
    }
    delete []RSUreturnbuf;
}
