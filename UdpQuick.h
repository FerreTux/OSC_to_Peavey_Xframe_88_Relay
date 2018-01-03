//
//  UdpQuick.h
//  TestApp
//
//  Created by Sophie Peters on 3/29/14.
//  Copyright (c) 2014 Pixoodles. All rights reserved.
//

#ifndef UdpQuick_h
#define UdpQuick_h
//////////Standard Includes
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstring>
#include "sstream"
///////////////////////Server Includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//////////////Server Defines
#define MAXBUF 1024*1024

class UdpServer
{
private:
    int _ld;
    struct sockaddr_in _skaddr;
    struct sockaddr_in _remote;
    int _length;
    bool STARTED;
    unsigned int _len;
    int _buffMax;
    int _n;
    unsigned char _bufin[MAXBUF];
public:
    UdpServer();
    unsigned char * pin();
    void pout(char * data, int size);
    bool start(short port);
    bool setInBuffer(int bufSize);
    int n();
};


bool UdpServer::setInBuffer(int bufSize)
{
    _buffMax = bufSize;
    return setsockopt(_ld,SOL_SOCKET,SO_RCVBUF,&_buffMax,sizeof(int));
}

int UdpServer::n()
{
    return _n;
}
UdpServer::UdpServer()
{
    STARTED = false;
    _ld = 0;
    _length = 0;
    _n = 16;
    
}

bool UdpServer::start(short port)
{
    if ((_ld = socket( PF_INET, SOCK_DGRAM, 0 )) < 0)
    {
        printf("UDP Server: Problem creating socket\n");
        STARTED = false;
        return false;
    }
    _skaddr.sin_family = AF_INET;
    _skaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    _skaddr.sin_port = htons(port);
    
    if (bind(_ld, (struct sockaddr *) &_skaddr, sizeof(_skaddr))<0)
    {
        printf("UDP Server: Problem binding\n");
        STARTED =false;
        return false;
    }
    _length = sizeof( _skaddr );
    printf("UDP Server: listening to port number %d\n",ntohs(_skaddr.sin_port));
    _len = sizeof(_remote);
    STARTED = true;
    
    return true;
}
unsigned char * UdpServer::pin()
{
    
    _n = recvfrom(_ld, &_bufin, MAXBUF, 0, (struct sockaddr *)&_remote, &_len);
    printf("\nUDP Server: Received datagram from %s port %d\n",
           inet_ntoa(_remote.sin_addr), ntohs(_remote.sin_port));
    _remote.sin_port = htons(9911);
    //int a = inet_aton("192.168.1.131",&_remote.sin_addr);
    if (_n<0)
        perror("UDP Server: Error receiving data");
    else
        printf("UDP Server: GOT %d BYTES\n",_n);
    for(int i = 0 ; i < _n; i++)
        std::cout << " "<< i << ":" << _bufin[i];
    return _bufin;
}

void UdpServer::pout(char * data, int size)
{
    sendto(_ld,data,size,0,(struct sockaddr *)&_remote,_len);
}



#endif
