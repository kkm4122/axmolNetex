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
    bool Recv(SOCKET sock);     //client의 recvdata 함수에서 호출 버퍼를 MAX_RECVBUF만큼 받아옴
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
/*리시브 과정    //mainscene
    클라이언트가 리시브데이터를 받는데 성공하면


*/
