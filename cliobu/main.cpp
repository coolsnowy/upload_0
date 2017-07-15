#include "main.h"
// define variable

tcp_client tcpcli;
extern char buf[500];
const char *filepath = "/etc/ini.json";
int main(int argc,char *argv[])
{
    //read paramter for the tcp program
    InitLogSystem(L_DEBUG, NULL);

    const char *RecvPort= 0;
    const char *ServIP= 0;
    const char *ServPort= 0;
    string s1,s2,s3;
    readfile(s1,s2,s3,filepath);
    RecvPort= s1.c_str();
    ServIP = s2.c_str();
    ServPort = s3.c_str();
    Debug("RecvPort is %s\n",RecvPort);
    Debug("ServIP is %s\n",ServIP);
    Debug("ServPort is %s\n",ServPort);

    int Serv_Port = atoi(ServPort);
    tcpcli.Connect(ServIP,Serv_Port);

    OBURegister_upload(buf);

    udprecv(RecvPort);
    tcpcli.Close();
    CloseLogSystem();
    return 0;
}
