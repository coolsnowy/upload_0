#include "tcpserv.h"
#include "log.h"
#include <fstream>
#include "unpack.h"
#include <assert.h>

const char * filename = "/etc/serv.txt";
bool tcp_serv::Listen(char *serv_port)
{
    //be zero server_addr
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    int port = atoi(serv_port);
    server_addr.sin_port = htons(port);
    // create tcp socket fd,
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        Debug("Create Socket Failed!\n");
        exit(1);
    }
    int opt = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)))
    {
        Debug("bind error\n");
        exit(1);
    }
    if (listen(sock_fd, 20))
    {
        Debug("Server Listen Failed!\n");
        exit(1);
    }
    return 1;
}
bool tcp_serv::tcp_send(char *buf,size_t len)
{
    int send_num;
    send_num = send(sock_fd, buf,len, 0);
    if (send_num < 0)
    {
          perror("server send error:");
          exit(1);
    }
    Debug("server send success\n");
    return true;
}

char * tcp_serv::tcp_recv()
{
    cout<<"tcp serv\n";
    Debug("tcp serv\n");
    ofstream in;
    in.open(filename,ios::out|ios::app);
    socklen_t peerlen = sizeof(server_addr);
    //char recv_buf[MAX] = "0";
    int i;
    int client[FD_SETSIZE];
    int maxi = 0;
    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;
    int nready;
    int maxfd = sock_fd;
    struct timeval timeout;
    fd_set rset;
    fd_set allset;
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    FD_SET(sock_fd, &allset);
    while (1)
    {
        cout<<endl<<endl<<"********************************waiting message\
********************************"<<endl<<endl;
        in<<endl;
        memset(recvbuf,0,sizeof(recvbuf));
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, &timeout);
        if (nready == -1)
        {
            if (errno == EINTR)
            continue;
        }
        if (nready == 0)
            continue;
        // detect if any new client
        if (FD_ISSET(sock_fd, &rset))
        {
            //Debug("enter\n");
            if (nready <= 0)
            {
                Debug("nready <=0\n");
                in << "nready <=0\n";
                continue;
            }
            //nready--;
            connfd = accept(sock_fd, (struct sockaddr*) &client_addr, &peerlen); //accept不再阻塞
            if (connfd == -1)
            {
                Debug("accept error\n");
                in << "accept error" << endl;
                continue;
            }
            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = connfd;
                    Debug("add client success!\n");
                    in << "add client success!\n";
                    break;
                }
            }
            if (i == FD_SETSIZE)
            {
                Debug("too many clients\n");
                in<< "too many clients\n";
                exit(1);
            }

            FD_SET(connfd, &allset);
            if (connfd > maxfd)
                maxfd = connfd;

            if (i > maxi)
            {
                maxi = i;
            }
            if(--nready <=0)
                continue;
        }
            for (i = 0; i <= maxi; i++)
            {
                if ((connfd = client[i]) < 0) /*invalid client*/
                {
                    Debug("client invalid\n");
                    in << "client invalid" << endl;
                    continue;
                }
                if (FD_ISSET(connfd, &rset)) /*judge if any */
                {
                    memset(data_head,0,sizeof(data_head));
                    int head_len = recv(connfd,data_head,6,0);
                    if(head_len ==-1)
                    {
                        Debug("head length error\n");
                        break;
                    }
                    else if (head_len  == 0)
                    { //close socket
                        Debug("client close \n");
                        FD_CLR(connfd, &allset);
                        client[i] = -1;
                        close(connfd);
                    }
                    else if(head_len <6)
                    {
                        Debug("len error,len<6 \n");
                        in<<"len error,len<6"<<endl;
                    }

                    int16_t data_len = 0;
                    data_len = ntohs(*(int16_t*)(data_head+4));
                    //debug
                    cout<<"data_len(just include data) = "<<data_len<<endl;
                    // add 1 to receive crc
                    int len = recv(connfd, recvbuf, data_len+1, 0);
                    if (len == -1)
                    {
                        Debug("readline error\n");
                        in << "readline error" << endl;
                        break;
                    }
                        //Debug("receive success\n");
                        in <<"receive success"<<endl;
                        Debug("recv %d bytes\n", len+head_len);
                        in <<endl<< "recv " << len+head_len << " bytes\n";
                        assert(recvbuf);
                        type_distinguish(data_head,recvbuf,connfd,len+head_len);
                    if (--nready <= 0)
                    break;
                }
            }

    }
    //FD_CLR(connfd, &allset);
    //client[i] = -1;
    return recvbuf;
}
void tcp_serv::Close()
{
    close(sock_fd);
}
