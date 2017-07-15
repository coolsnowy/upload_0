#ifndef TCPSERV_H
#define TCPSERV_H

#include<iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "log.h"
#include <fstream>
using namespace std;
#define SENDTIMES 100
#define MAXLINE 500
#define MAXSELECT 30
#define MAX  1000


class tcp_serv
{
private:
        struct sockaddr_in server_addr, client_addr;
        int sock_fd;
        int connfd;
        char recvbuf[1000];
        char data_head[10];

public:
        bool Listen(char *serv_port);
        char *tcp_recv();
        bool tcp_send(char *buf,size_t len);
        void Close();
};


#endif // TCPSERV_H
