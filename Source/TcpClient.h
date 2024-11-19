 #pragma once
#include <winsock2.h>
#include "axmol.h"
#include "MainScene.h"
enum class DT
{
    REQUESTACTOR = 5,
    POS,
    SOCKETDATA,
    DELETEACTOR
    
};

class Receive;
using namespace ax;
class TcpClient
{
    
public:
	TcpClient(const char* ip, unsigned short port);
	~TcpClient();
	bool SendSample();
	bool SendChat();
	bool RecvData();
    

	bool Select(struct timeval timeout);




    bool SendPos();
    bool SendReqActor();
    bool SendData();
    bool SendDelete();
    char* GetPacket();
    bool RecvDataS();
    void endRecv();
    CDat dat;
    CDat Rdat;
    char RecvBuf[1024] = {0,};
    
    Receive* mRecv = nullptr;
	
private:
	bool CreateClientSocket(const char* ip, unsigned short port);
    
	SOCKET mSocket;
	unsigned short mPort;
	int buflen = 0;
	bool inputkey = false;
    
};

