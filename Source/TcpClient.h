 #pragma once
#include <winsock2.h>
#include "axmol.h"
#include "MainScene.h"
enum class DT   //보내는 데이터 타입(data type)
{
    REQUESTACTOR = 5,   //액터 생성 요청
    POS,                //좌표
    SOCKETDATA,         //request를 받은 클라이언트의 데이터 요청
    DELETEACTOR         //액터 제거 요청
    
};

class Receive;
using namespace ax;
class TcpClient
{
    
public:
	TcpClient(const char* ip, unsigned short port);
	~TcpClient();
    //샘플 함수들
	bool SendSample();
	bool SendChat();
	bool RecvData();
    


	bool Select(struct timeval timeout);//연결된 소켓에 신호가 왔는지 확인



    //DT(data Type)에 맞는 버퍼 보내기
    bool SendPos();
    bool SendReqActor();
    bool SendData();
    bool SendDelete();

    //리시브 클래스 함수 호출
    char* GetPacket();
    bool RecvDataS();
    void endRecv();
    CDat dat;

    //CDat Rdat;//리시브 데이터
    //char RecvBuf[1024] = {0,};리시브 클래스가 가지고 있으므로 더이상 사용할 필요가 없음
    
    Receive* mRecv = nullptr;
	
private:
	bool CreateClientSocket(const char* ip, unsigned short port);
    
	SOCKET mSocket;
	unsigned short mPort;//서버에 연결된 포트번호
	int buflen = 0;
	bool inputkey = false;
    
};

