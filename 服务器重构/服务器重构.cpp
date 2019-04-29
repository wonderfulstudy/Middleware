// 服务器重构.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Link.h"

#pragma	comment(lib, "ws2_32.lib")
using namespace std;

#define BUFFSIZE 1024

DWORD WINAPI THREAD_TCP_RECV(LPVOID lpParamter)
{
	ofstream in("test.txt");
	char BUFF[BUFFSIZE];
	Link recv;

	while (true)
	{
		recv.reciveDATA(BUFF);
		if (!in.is_open())
		{
			cout << "打开文件失败！";
			exit(1);
		}
		in << BUFF;
		in.close();
	}
	return 0L;
}

int main()
{
	HANDLE TCP_RECV = CreateThread(NULL, 0, THREAD_TCP_RECV, NULL, 0, NULL);


	CloseHandle(TCP_RECV);
    return 0;
}

