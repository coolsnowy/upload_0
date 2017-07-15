#include "package.h"
extern tcp_client tcpcli;
void add_head(char framebuf[],char &frameType,int16_t Length,char buf[])
{

    char Head[2] = { 0x59, 0x5A };
    //1 frame begin with 0x595A
    *framebuf = Head[0];
    framebuf++;
    *framebuf = Head[1];
    framebuf++;
    //2 protocol version
    *framebuf++ = 0x01;
    //3.1 frameType
    *framebuf++ = frameType;
    //3.2 data_length short int
    *(int16_t *)framebuf = htons(Length);
    framebuf +=1;
    //3.3 data
    int bufi = 0;
    cout<<"lenght of buf before frame = "<<Length<<endl;
    for (bufi = 0; bufi < Length && bufi<1000; bufi++)
    {
        framebuf++;
        *framebuf = buf[bufi];
    }

    //cout<<"frame struct success\n";
}
int16_t Getlen(char *buf,int bufsize)
{
    int16_t len=0;
    while(buf[len] && len < bufsize)
    {
        len++;
    }
    return len;
}

void frame(char &frametype,char *buf)
{
    Debug("frame\n");
    char *framebuf = new char [300];
    memset(framebuf,0,300);
    int16_t buf_len =  Getlen(buf,500);
    add_head(framebuf,frametype,buf_len,buf);
    cout<<"framebuf: ";
    for(int i=0;i<buf_len+7;i++)
    {
        printf("%02hhX ",framebuf[i]);
    }cout<<endl;
    tcpcli.send_data(framebuf,buf_len+7);
    delete []framebuf;

}
