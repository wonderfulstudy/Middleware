#include "stdafx.h"
#include "Link.h"


Link::Link()
{
}


Link::~Link()
{
}

int Link::sendDATA(char * BUFF)
{
	if ((err = WSAStartup(MAKEWORD(2, 2), &wsaData)) == 0)
	{
		SOCKET	send_socket;
		SOCKADDR_IN		client_sockaddr;

		int	sendLen;

		if ((send_socket = socket(PF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET)
		{
			client_sockaddr.sin_family = PF_INET;
			client_sockaddr.sin_port = htons(client_port);
			inet_pton(PF_INET, client_IP, &client_sockaddr.sin_addr.S_un.S_addr);
			//client.sin_addr.S_un.S_addr = inet_addr(client_IP);

			connect(send_socket, (struct sockaddr*)&client_sockaddr, sizeof(sockaddr));
			if (sendLen = send(send_socket, BUFF, strlen(BUFF) + sizeof(char), 0) > 0)
			{
				printf_s("数据发送成功！");
			}
			else
			{
				printf_s("数据发送失败！");
			}

			closesocket(send_socket);
			WSACleanup();
		}
		else
		{
			printf_s("SOCKET创建失败！失败原因：%d", send_socket);
			return send_socket;
		}
	}
	else
	{
		printf_s("SOCKET文件打开失败！错误为：%d", err);
		return err;
	}
	return 0;
}

int Link::reciveDATA(char * BUFF)
{
	if ((err = WSAStartup(MAKEWORD(2, 2), &wsaData)) == 0)
	{
		SOCKET	recive_socket;
		SOCKET	accept_socket;
		SOCKADDR_IN		client_address;
		SOCKADDR_IN     server_socket;

		int client_len = sizeof(SOCKADDR_IN);
		int ret;

		if ((recive_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET)
		{
			server_socket.sin_family = AF_INET;
			server_socket.sin_port = htons(server_port);
			server_socket.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
			//inet_pton(PF_INET, INADDR_ANY, &server.sin_addr.S_un.S_addr);

			if (bind(recive_socket, (struct sockaddr*)&server_socket, sizeof(sockaddr)) == SOCKET_ERROR)
			{
				printf_s("SOCKET绑定失败！");

				return 0;
			}
			if (listen(recive_socket, 1) == SOCKET_ERROR)
			{
				printf_s("SOCKET监听失败！");

				return 0;
			}
			accept_socket = accept(recive_socket, (struct sockaddr*)&client_address, &client_len);


			ret = recv(accept_socket, BUFF, BUFFSIZE, 0);
			BUFF[ret] = '\0';

			closesocket(recive_socket);
			WSACleanup();
		}
		else
		{
			printf_s("SOCKET创建失败！失败原因：%d", recive_socket);
			return recive_socket;
		}
	}
	else
	{
		printf_s("SOCKET文件打开失败！错误为：%d", err);
		return err;
	}
	return 0;
}
