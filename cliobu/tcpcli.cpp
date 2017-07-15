
#include "tcpcli.h"
using namespace std;
bool tcp_client::Connect(const char ipaddress[], int &destport)
{
    //set a socket address struct --server_addr , it represents server IP and PORT
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if (inet_aton(ipaddress, &server_addr.sin_addr) == 0) //server IP is from procedure arguments
    {
        cout << "Server IP Address Error!\n" << endl;
        exit(1);
    }

    // bzero(&client_addr, sizeof(client_addr));
    memset(&client_addr,0,sizeof(client_addr));
    client_addr.sin_family = AF_INET;    //internet protocal
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);    //INADDR_ANY represent any address
    client_addr.sin_port = htons(0);    //0 represent the port that is allocatad by system automatically
    //create the TCP socket stream protocal for internet, use client_socket represent client socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        cout << "Create Socket Failed!\n";
        exit(1);
    }
    //associate the socket address with sock_fd
    if (bind(sock_fd, (struct sockaddr*) &client_addr, sizeof(client_addr)))
    {
        printf("Client Bind Port Failed!\n");
        exit(1);
    }

    server_addr.sin_port = htons(destport);
    socklen_t server_addr_length = sizeof(server_addr);
    //connect to server,client socket represent a connect when connecting successful
    if (connect(sock_fd, (struct sockaddr*) &server_addr,
            server_addr_length) < 0)
    {
        printf("Can Not Connect To %s!\n", ipaddress);
        exit(1);
    }
    else
        cout << "connect success" << endl;

    return true;
}
bool tcp_client::send_data(char *sendbuf,size_t len)
{
    int send_num;
    send_num = send(sock_fd, sendbuf,len, 0);
    if (send_num < 0)
    {
        cout<<"send failure! exit!"<<endl;
          perror("client send error:");
          exit(1);
    }
    else
          cout<<"client send success"<<endl;
    return true;
}
char* tcp_client::recv_data(char recv_buf[])
{

    int recv_num = recv(sock_fd, recv_buf, strlen(recv_buf), 0);
    if (recv_num < 0)
    {
        perror("recv error");
        exit(1);
    }
    return recv_buf;
}
void tcp_client::Close()
{
    close(sock_fd);
}


