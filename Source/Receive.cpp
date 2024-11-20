#include "Receive.h"

Receive::Receive()
{
    mFirst = 0;
    mLast  = 0;
    packetLen = 0;
}

Receive::~Receive()
{

}

bool Receive::Recv(SOCKET sock)
{
    int r = recv(sock, recvBuf + mLast, MAX_RECVBUF - mLast - 1, 0);
    if (r <= 0) { return false; }

    mLast += r;//라스트 전체 패킷의 크기

    return true;
}

// while (b = client->GetPacket())
char* Receive::GetPacket()      
{
    if (CheckPacketLen())
    {
        if (recvBuf[mFirst] != ID)
        {
            mFirst += packetLen;
            return nullptr;
        }

        char* data = recvBuf + mFirst + 1 + SIZE_PACKETSIZENUM;
        memcpy(packet, data, packetLen - 1 - SIZE_PACKETSIZENUM);
        mFirst += packetLen;//쓰고 안읽은 버퍼 초기주소값(여기부터 읽어라)

        return packet;
    }
    
    return nullptr;
}

bool Receive::CheckPacketLen()
{
    if (mFirst == mLast) { return false; }//버퍼 전체의 길이가 0일되면

    packetLen = 0;
    BYTE id   = recvBuf[mFirst];
    packetLen += 1;                     // ID Size

    short len = 0;
    memcpy(&len, recvBuf + mFirst + 1, SIZE_PACKETSIZENUM);//len=받아올 데이터  Size 
    packetLen += SIZE_PACKETSIZENUM;    // Sizeof(short) bufsize Size
    packetLen += len;                   // len=받아올 데이터  Size    

    if (mLast - mFirst < packetLen) { return false; }

    return true;
}

void Receive::End()
{
    if (mFirst < mLast)
    {
        memmove_s(recvBuf, MAX_RECVBUF, recvBuf + mFirst, mLast - mFirst);
        mLast -= mFirst;
        mFirst = 0;
        return;
    }
    else
    {
        mLast = 0;
        mFirst = 0;
    }
}
