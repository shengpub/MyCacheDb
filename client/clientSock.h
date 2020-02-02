#pragma once
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std ;

class clientSock
{
public:
    clientSock() { sockFd = -1 ;}
    ~clientSock() {close(sockFd) ;}
public :
    int anetCreateSock() ;
    int clientConnect(string ip, string port) ;
    int setnoBlocking() ;
private:
    int sockFd ;
    struct sockaddr_in addr ;
};
