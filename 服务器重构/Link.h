#pragma once
#include<WinSock2.h>
#include<Windows.h>
#include<WS2tcpip.h>

#define BUFFSIZE		1024
#define server_port		6000
#define client_IP		"127.0.0.1"
#define client_port		6000

class Link
{
public:
	Link();
	~Link();
	int sendDATA(char *BUFF);
	int reciveDATA(char *BUFF);
private:
	WSADATA	wsaData;
	int		err;
};

