#ifndef TCPCLI_H
#define TCPCLI_H

#include<iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<sys/time.h>
#include <netinet/in.h>
#include<ctype.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SENDTIMES 100
#define MAX 500
class tcp_client
{
private:
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int sock_fd;

public:
        bool Connect(const char *ipaddress, int & destport);
        bool send_data(char *sendbuf,size_t len);
        char* recv_data(char recv_buf[]);
        void Close();
};



#endif // TCPCLI_H
