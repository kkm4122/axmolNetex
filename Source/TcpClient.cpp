//#include "pch.h"
#pragma once
#include "axmol.h"
#include "TcpClient.h"
#include <stdio.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include "Receive.h"
#include < conio.h >
#pragma comment(lib, "ws2_32")
using namespace std;
bool g_TcpNetworkInited = false;

bool Init_TCP() {
	if (g_TcpNetworkInited) return true;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)//MAKEWORD (2.2버전)
		return true;

	return false;
}

void Close_TCP() {
	if (g_TcpNetworkInited) WSACleanup();

	g_TcpNetworkInited = false;
}

TcpClient::TcpClient(const char* ip, unsigned short port)
{
	printf("클라이언트 생성자\n");
	Init_TCP();

    mRecv = new Receive;
    CreateClientSocket(ip, port);
}

TcpClient::~TcpClient()
{
	printf("클라이언트 소멸\n");
    delete mRecv;
	closesocket(mSocket);
	Close_TCP();
}

bool TcpClient::SendSample()
{
	char buf[1024];
	
	sprintf_s(buf, "%d %d ABCD", mPort, mSocket);
	int len = strlen(buf) + 1;
	int r = send(mSocket, buf, len, 0);
	if (r == SOCKET_ERROR) return false;

	printf("Send... \n");
	return true;
}

bool TcpClient::SendChat()
{
	inputkey = false;
	
	if (_kbhit())
	{
		int key = _getch();
		if (key == 13)
		{
			//printf
			inputkey = true;
		}
		else if(key==8)
		{	
			//Chatbuf[--buflen] = 0;
			printf("\r");
			printf("\t\t\t\t\r");
		//	printf("%s", Chatbuf);
		}
		else
		{
			//Chatbuf[buflen++] = key;
			printf("%c", key);
		}
	}
	if (inputkey)
	{

	//int r = send(mSocket,Chatbuf,buflen,0);
	//if (r == SOCKET_ERROR) return false;
	for (int i = 0; i < buflen; i++)
	{
		//Chatbuf[i] = 0;
	}
	buflen = 0;
	printf("Send... \n");
	
	}

	return true;
}

bool TcpClient::RecvData()
{
	char buf1[1024];
	
	
	int r = recv(mSocket, buf1, 1024, 0);
	string str = string(buf1);
	//string str = string(buf1);
	if (r > 0) {
		//buf1[r] = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '(')
			{
				
				cout << "사용자 " << str.substr(i,i+2) << " : " << str.substr(0,i-1) << "\n";
				return true;
			}
		}
		
		return true;
	}

	return false;
}

bool TcpClient::Select(timeval timeout)
{
	FD_SET rset;

	FD_ZERO(&rset);
	FD_SET(mSocket, &rset);

	int fd_num = select(0, &rset, nullptr, nullptr, &timeout);//신호가 오면 fd_num에 값이 증가

	return fd_num > 0;
}

bool TcpClient::SendPos()
{
    char buf[1024] = {
        0,
    };
    char msgNum = 14;
    short size  = 0;
    int a       = 0;
    a += sizeof(msgNum);
    memcpy(buf, &msgNum, sizeof(msgNum));
    // size += sizeof(msgNum);
    size += sizeof(DT);
    size += sizeof(CDat);
    memcpy(buf + a, &size, sizeof(size));
    // size += sizeof(size);
    a += sizeof(size);
    DT sendType = DT::POS;
    memcpy(buf + a, &sendType, sizeof(sendType));
    a += sizeof(DT);
    CDat Send;
    Send = dat;

    memcpy(buf + a, &Send, sizeof(Send));
    a += sizeof(CDat);
    int r   = send(mSocket, buf, a, 0);
    if (r == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

bool TcpClient::SendMove()
{
    char buf[1024] = {
        0,
    };
    char msgNum = 14;
    short size  = 0;
    int a       = 0;
    a += sizeof(msgNum);
    memcpy(buf, &msgNum, sizeof(msgNum));
    // size += sizeof(msgNum);
    size += sizeof(DT);
    size += sizeof(CDat);
    memcpy(buf + a, &size, sizeof(size));
    // size += sizeof(size);
    a += sizeof(size);
    DT sendType = DT::MOVE;
    memcpy(buf + a, &sendType, sizeof(sendType));
    a += sizeof(DT);
    CDat Send;
    Send = dat;

    memcpy(buf + a, &Send, sizeof(Send));
    a += sizeof(CDat);
    int r = send(mSocket, buf, a, 0);
    if (r == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

bool TcpClient::SendReqActor()
{
    char buf[1024] = {
        0,
    };
    char msgNum = 14;
    short size  = 0;
    int a       = 0;
    a += sizeof(msgNum);
    memcpy(buf, &msgNum, sizeof(msgNum));
    // size += sizeof(msgNum);
    size += sizeof(DT);
    size += sizeof(CDat);
    memcpy(buf  + a, &size, sizeof(size));
    // size += sizeof(size);
    a += sizeof(size);
    DT sendType = DT::REQUESTACTOR;
    memcpy(buf + a, &sendType, sizeof(sendType));
    a += sizeof(DT);
    CDat Send;
    Send = dat;

    memcpy(buf + a, &Send, sizeof(Send));
    a += sizeof(CDat);
    int r = send(mSocket, buf, a, 0);
    if (r == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

bool TcpClient::SendData()
{
    char buf[1024] = {
        0,
    };
    char msgNum = 14;
    short size  = 0;
    int a       = 0;
    a += sizeof(msgNum);
    memcpy(buf, &msgNum, sizeof(msgNum));
    // size += sizeof(msgNum);
    size += sizeof(DT);
    size += sizeof(CDat);
    memcpy(buf + a, &size, sizeof(size));
    // size += sizeof(size);
    a += sizeof(size);
    DT sendType = DT::SOCKETDATA;
    memcpy(buf + a, &sendType, sizeof(sendType));
    a += sizeof(DT);
    CDat Send;
    Send = dat;

    memcpy(buf + a, &Send, sizeof(Send));
    a += sizeof(CDat);
    int r = send(mSocket, buf, a, 0);
    if (r == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

bool TcpClient::SendDelete()
{
    char buf[1024] = {
        0,
    };
    char msgNum = 14;
    short size  = 0;
    int a       = 0;
    a += sizeof(msgNum);
    memcpy(buf, &msgNum, sizeof(msgNum));
    // size += sizeof(msgNum);
    size += sizeof(DT);
    size += sizeof(CDat);
    memcpy(buf + a, &size, sizeof(size));
    // size += sizeof(size);
    a += sizeof(size);
    DT sendType = DT::DELETEACTOR;
    memcpy(buf + a, &sendType, sizeof(sendType));
    a += sizeof(DT);
    CDat Send;
    Send = dat;

    memcpy(buf + a, &Send, sizeof(Send));
    a += sizeof(CDat);
    int r = send(mSocket, buf, a, 0);
    if (r == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

bool TcpClient::SendDT(DT dt)
{
    char buf[1024] = {
        0,
    };
    char msgNum = 14;
    short size  = 0;
    int a       = 0;
    a += sizeof(msgNum);
    memcpy(buf, &msgNum, sizeof(msgNum));
    // size += sizeof(msgNum);
    size += sizeof(DT);
    size += sizeof(CDat);
    memcpy(buf + a, &size, sizeof(size));
    // size += sizeof(size);
    a += sizeof(size);
    DT sendType = dt;
    memcpy(buf + a, &sendType, sizeof(sendType));
    a += sizeof(DT);
    CDat Send;
    Send = dat;

    memcpy(buf + a, &Send, sizeof(Send));
    a += sizeof(CDat);
    int r = send(mSocket, buf, a, 0);
    if (r == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

char* TcpClient::GetPacket()
{
    return mRecv->GetPacket();
}



bool TcpClient::RecvDataS()
{
    
    //char Rbuf[4096];

    //RecvBuf
    //int r      = recv(mSocket, RecvBuf, 1024, 0);

    return mRecv->Recv(mSocket);



   // printf("r=%d\n",r);
    
    
    //if (r > 0)
    //{
    //    //memcpy(Rbuf,buf1,strlen(buf1));
    //    char t ;
    //    memcpy(&t, RecvBuf, sizeof(char));
    //    if (t != 14)
    //    {
    //        return false;
    //    }
    //    
    //    
    //    
    //    return true;
    //}

    //return false;
}

void TcpClient::endRecv() {
    mRecv->End();
}

bool TcpClient::CreateClientSocket(const char* ip, unsigned short port)
{
	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET) { return false; }

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &serveraddr.sin_addr);//listen과는 다르게 연결을 해야할 주소를 알아야 하니까 pointer to number 주소를 정확히 알아야 하니까 
	serveraddr.sin_port = htons(port);			//host to number 포트넘버

	//u_long on = 1;
	//int r = ioctlsocket(mSocket, FIONBIO, &on); //블로킹작업 나중에 쓸

	int r = connect(mSocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));//mSocket을 서버에 커넥트 해라 이때 mSocket addr은 자동으로 생긴다.
	if (r == SOCKET_ERROR) { return false; }//커넥트 체크

	//내 주소 받을 소켓을addr을 만들고 확인할 용도 포트넘버를 받기위해
	SOCKADDR_IN my_addr;			
	int addr_len = sizeof(my_addr);	//주소 길이
	getsockname(mSocket, (sockaddr*)&my_addr, &addr_len);//소켓addr정보
	mPort = ntohs(my_addr.sin_port);//my_addr 포트넘버

	printf("Connect 성공\n");
       
    recv(mSocket, (char*)&dat.id, 4, 0);
        
    printf("아이디 : %d \n",dat.id);
    return true;
}
