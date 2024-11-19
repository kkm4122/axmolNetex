#pragma once
#include <winsock2.h>

#define ID 14
#define SIZE_PACKETSIZENUM 2 // sizeof(short)
#define MAX_RECVBUF 4096

class Receive
{
public:
    Receive();
    ~Receive();

public:
    bool Recv(SOCKET sock);
    char* GetPacket();
    void End();

private:
    bool CheckPacketLen();//받은 버퍼의 크기(길이) 확인

    char packet[MAX_RECVBUF] = { 0, };
    char recvBuf[MAX_RECVBUF] = { 0, };
    int mFirst;
    int mLast;
    short packetLen;
};
