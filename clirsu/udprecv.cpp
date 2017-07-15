#include "udprecv.h"
using namespace std;
void udprecv(const char *RecvPort)
{
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int recvport = atoi(RecvPort);
    if(recvport <0)
    {
        Debug("RecvPort error!\n");
        exit(1);
    }
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0)
    {
        Debug("recv socket error\n");
        exit(1);
    }
    struct sockaddr_in addr_serv, addr_cli;
    memset(&addr_serv, 0, sizeof(struct sockaddr_in));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(recvport);
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&addr_serv.sin_zero, 8);
    int addr_len = sizeof(addr_serv);

    addr_cli.sin_family = AF_INET;
    addr_cli.sin_port = htons(10001);
    addr_cli.sin_addr.s_addr = INADDR_ANY;
    bzero(&addr_cli.sin_zero, 8);

    if (bind(sock_fd, (struct sockaddr *) &addr_serv, sizeof(addr_serv)) < 0)
    {

        Debug("bind error\n");
        exit(1);
    }
    int maxfd = sock_fd;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock_fd, &readfds);// add the sock_fd to allset
    vector<uint8_t> recv_vector;
    uint8_t recv_buf[MAXLINE];
    int nready = 0;
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(sock_fd, &readfds);
        // it is so important
        recv_vector.clear();
        memset(recv_buf,0,MAXLINE);
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        //get the number of fd we can obtain present
        nready = select(maxfd + 1, &readfds, NULL, NULL, &timeout);
        if (nready <= 0)
            continue;
        if (FD_ISSET(sock_fd, &readfds)) //judge if any socketfd to read
        {
            int recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0,
                    (struct sockaddr *) &addr_cli,
                    (socklen_t *) &addr_len);
            if (recv_num < 0)
            {
                Debug("recvfrom error");
                exit(1);
            }
            /*
             * for(int i= 0;i<recv_num;i++)
            {
                printf("%02X ",recv_buf[i]);
            }cout<<endl;
            */
            Debug("UDP recv %d bytes from ( %s:%d )\n",
                  recv_num,inet_ntoa(addr_cli.sin_addr),
                  ntohs(addr_cli.sin_port));
            for(int num=0;num<recv_num;num++)
            {
                recv_vector.push_back(recv_buf[num]);
            }
            data_process(recv_vector,recv_buf,recv_num);
            /*
             * for(auto i: recv_vector)
                printf("%02X ",i);
            cout<<endl;
            */
        }
    }

    close(sock_fd);
}
