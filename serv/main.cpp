#include "tcpserv.h"
#include "unpack.h"
#include "log.h"
int main(int argc, char* argv[])
{
    InitLogSystem(L_DEBUG, NULL);
    //char recv_buf[1000];
    tcp_serv serv;
    serv.Listen(argv[1]);
    cout << "listen success!\n";
    serv.tcp_recv();
    CloseLogSystem();
    return 0;
}
