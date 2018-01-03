//
//  SerialWriter.h
//  TestApp
//
//  Created by Sophie Peters on 3/29/14.
//  Copyright (c) 2014 Pixoodles. All rights reserved.
//

#ifndef SerialWriter_h
#define SerialWriter_h

//////////Standard Includes
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstring>
#include "sstream"

////////////////Serial Includes
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>


////////Serial Defines
#define BD19200 B19200
#define BD9600 B9600
#define BD110 B110
#define BD600 B600
#define BD2400 B2400
#define BD38400 B38400
#define BD57600 B57600
#define BD300 B300
#define BD1200 B1200
#define BD4800 B4800
#define BD14400 B14400
#define BD28800 B28800
#define BD56000 B56000
#define BD115200 B115200
#define BD128000 B128000
#define BD230400 B230400
#define BD460800 B460800
#define BD153600 B153600
#define BD256000 B256000
#define BD921600 B921600
#define SR_BUFMAX 512

class SerialWriter
{
private:
    termios _tio;
    int _fd,_n, _nr;
    char _rb;
    char _rl [SR_BUFMAX];
    bool CONNECTED;
    void clrBuff();
public:
    SerialWriter();
    int n();
    bool connect(std::string dvc, int baud);
    void sout(unsigned char * line, unsigned short length);
    char * sin(char * stopBytes, int numOfStopBytes);
    char * sin();
};
int SerialWriter::n() { return _nr; }

bool SerialWriter::connect(std::string dvc, int baud)
{
    _fd = open(dvc.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (_fd==-1)
    {
        perror("failed to open");
        CONNECTED = false;
        return false;
    }
    else
    {
        fcntl(_fd, F_SETFL, 0);
        switch (baud)
        {
            case 19200:
                _tio.c_cflag |= BD19200;
                break;
            default:
                std::cout << "Serial Writer: Invalid Baud Selected:"
                << "               Supported Buads: 19200 " << std::endl;
                CONNECTED = false;
                return false;
                break;
        }
        _tio.c_cflag |= CS8 | CLOCAL | CREAD;
        _tio.c_iflag = IGNPAR | IGNCR;
        _tio.c_oflag = 0;
        _tio.c_cc[VTIME] =  0;
        _tio.c_cc[VMIN]  =  1;
        tcflush(_fd,TCIFLUSH);
        tcsetattr(_fd, TCSANOW, &_tio);
        CONNECTED = true;
        return true;
    }
}
SerialWriter::SerialWriter()
{
    _fd = 0;
    _n = 0;
    CONNECTED = false;
    
}

void SerialWriter::sout(unsigned char * line, unsigned short length)
{
    if (!CONNECTED)
    {
        std::cout << "Serial Writer: Serial Not Connected" << std::endl;
        return;
    }
    _n= write(_fd,line, length);
    if(_n<0)
        fputs("Serial Writer: Write Failed with error ", stderr);
    else
        std::cout << "Serial Writer: Serial Out Wrote " << line << std::endl;
}

char * SerialWriter::sin()
{
    if (!CONNECTED)
    {
        std::cout << "Serial Writer: Serial Not Connected" << std::endl;
        return "";
    }
    _nr = 0;
    int p = 0;
    clrBuff();
    bool STOP = false;
    fcntl(_fd, F_SETFL,FNDELAY);
    do
    {
        //usleep(100000);
        _n = read(_fd,&_rb, 1);
        if(_n > 0)
        {
            //std::cout << "rb: " << _rb << " " <<std::flush;
            if (p > 6)
                p = 0;
            _rl[p] = _rb;
            p++;
            _n++;
            if( _rb == '.' || _rl[6] == '?')
                STOP = true;
        }
    }while(!STOP);
    //std::cout <<"Delay:"<< _nr <<" "<< std::flush;
    return _rl;
}


void SerialWriter::clrBuff()
{
    for (int i = 0; i < 6; i++)
    {
        _rl[i] = 0;
    }
}
#endif
