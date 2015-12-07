/*
 * CommWithDisplayBase.cpp
 *
 *  Created on: 2015-12-5
 *      Author: andy
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include "CommWithDisplayBase.h"
#include "LogCat.h"


CommWithDisplayBase::CommWithDisplayBase():
	m_sevSockFd(-1)
{
	m_pRecvBuff = NULL;
	m_pSendBuff = NULL;
}

CommWithDisplayBase::~CommWithDisplayBase()
{

}

/**brief
 * 函数功能：初始化Socket通信，选用TCP协议
 * 参数说明：无
 * 返回值：错误码
 * 		0  成功
 * 		other 失败
 */
int CommWithDisplayBase::Init()
{
	/* 初始化接收缓存 */
	if (NULL == m_pRecvBuff)
	{
		m_pRecvBuff = new char[MAX_RECV_BUFFER_LENGTH];
		if (NULL == m_pRecvBuff)
		{
			LOG_INFO("new buffer for recv data failed err:%s", strerror(errno));
			return FAILED_NEW_RECV_BUFF;
		}

		memset(m_pRecvBuff, 0, MAX_RECV_BUFFER_LENGTH);
	}

	/* 初始化发送缓存 */
	if (NULL == m_pSendBuff)
	{
		m_pSendBuff = new char[MAX_SEND_BUFFER_LENGTH];
		if (NULL == m_pSendBuff)
		{
			LOG_INFO("new buffer for send data failed err:%s", strerror(errno));
			return FAILED_NEW_SEND_BUFF;
		}

		memset(m_pSendBuff, 0, MAX_SEND_BUFFER_LENGTH);
	}

	/* 创建POSIX Socket */
	if (-1 == m_sevSockFd)
	{
		m_sevSockFd = socket(AF_INET, SOCK_STREAM, 0);
		if (-1 == m_sevSockFd)
		{
			LOG_INFO("socket failed err:%s", strerror(errno));
			return FAILED_SCOKET;
		}

	}

	/* 绑定socket地址 */
	struct sockaddr_in sockaddr;
	memset((void*)&sockaddr, 0, (int)sizeof(sockaddr));
	/* 选定协议簇 */
	sockaddr.sin_family = AF_INET;
	/* 绑定到所有地址 */
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* 将端口号转换为网络字节序 */
	sockaddr.sin_port = htons(PORT);

	/* 绑定socket */
	if (-1 == bind(m_sevSockFd, (struct sockaddr*)&sockaddr, (int)sizeof(sockaddr)))
	{
		LOG_INFO("bind failed err:%s", strerror(errno));
		return FAILED_BIND;
	}

	/* 监听服务socket */
	if (-1 == listen(m_sevSockFd, 1))
	{
		LOG_INFO("listen failed err:%s", strerror(errno));
		return FAILED_LISTEN;
	}

	struct sockaddr_in addr;
	memset((void*)&addr, 0, (int)sizeof(addr));
	int addrLength = (int)sizeof(addr);
	/* 接收来自于UI的socket请求 */
	m_clientSockFd = accept(m_sevSockFd, (struct sockaddr*)&addr, &addrLength);
	if (-1 == m_clientSockFd)
	{
		LOG_INFO("accept failed err:%s", strerror(errno));
		return FAILED_ACCEPT;
	}
	return SUCCESS;
}

/** brief
 *  函数功能：从Sokcet中读取数据
 *  参数说明：pBuffer[out] 从Socket中读取到的数据
 *  	  len[in] pBuffer的长度
 *  返回值：实际读取到数据长度
 *       -1 读取失败
 */
int CommWithDisplayBase::GetData(char* pBuffer, int len)
{
	if (NULL == pBuffer)
	{
		LOG_INFO("GetData failed err:the buffer what is to receive data from socket is NULL");
		return -1;
	}
	if (len <= 0)
	{
		LOG_INFO("GetData failed err:len <= 0");
		return -1;
	}

	ssize_t recvSize = recv(m_clientSockFd, pBuffer, len - 1, 0);
	if (-1 == recvSize)
	{
		LOG_INFO("GetData failed err:%s", strerror(errno));
	}
	return recvSize;
}

/** brief
 *  函数功能：向Socket中写入数据
 *  参数说明：pBuffer[in] 待写入的数据内容
 *  	  len[in] pBuffer的长度
 *  返回值：实际读取到数据长度
 *       -1 写入失败
 */
int CommWithDisplayBase::SendData(const char* pBuffer, int len)
{
	if (NULL == pBuffer)
	{
		LOG_INFO("SendData failed err:the buffer what is to send data to socket is NULL");
		return -1;
	}
	if (len <= 0)
	{
		LOG_INFO("SendData failed err:len <= 0");
		return -1;
	}

	int sendSize = send(m_clientSockFd, pBuffer, len, 0);

	if (-1 == sendSize)
	{
		LOG_INFO("SendData failed err:%s", strerror(errno));
	}
	return sendSize;
}

void CommWithDisplayBase::free(){

	if (-1 != m_clientSockFd) {
		close(m_clientSockFd);
		m_clientSockFd = -1;
	}

	if (-1 != m_sevSockFd) {
		close(m_sevSockFd);
		m_sevSockFd = -1;
	}

	if (NULL != m_pSendBuff)
	{
		delete[] m_pSendBuff;
		m_pSendBuff = NULL;
	}

	if (NULL != m_pRecvBuff) {
		delete[] m_pRecvBuff;
		m_pRecvBuff = NULL;
	}
}
