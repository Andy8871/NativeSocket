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
 * �������ܣ���ʼ��Socketͨ�ţ�ѡ��TCPЭ��
 * ����˵������
 * ����ֵ��������
 * 		0  �ɹ�
 * 		other ʧ��
 */
int CommWithDisplayBase::Init()
{
	/* ��ʼ�����ջ��� */
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

	/* ��ʼ�����ͻ��� */
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

	/* ����POSIX Socket */
	if (-1 == m_sevSockFd)
	{
		m_sevSockFd = socket(AF_INET, SOCK_STREAM, 0);
		if (-1 == m_sevSockFd)
		{
			LOG_INFO("socket failed err:%s", strerror(errno));
			return FAILED_SCOKET;
		}

	}

	/* ��socket��ַ */
	struct sockaddr_in sockaddr;
	memset((void*)&sockaddr, 0, (int)sizeof(sockaddr));
	/* ѡ��Э��� */
	sockaddr.sin_family = AF_INET;
	/* �󶨵����е�ַ */
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* ���˿ں�ת��Ϊ�����ֽ��� */
	sockaddr.sin_port = htons(PORT);

	/* ��socket */
	if (-1 == bind(m_sevSockFd, (struct sockaddr*)&sockaddr, (int)sizeof(sockaddr)))
	{
		LOG_INFO("bind failed err:%s", strerror(errno));
		return FAILED_BIND;
	}

	/* ��������socket */
	if (-1 == listen(m_sevSockFd, 1))
	{
		LOG_INFO("listen failed err:%s", strerror(errno));
		return FAILED_LISTEN;
	}

	struct sockaddr_in addr;
	memset((void*)&addr, 0, (int)sizeof(addr));
	int addrLength = (int)sizeof(addr);
	/* ����������UI��socket���� */
	m_clientSockFd = accept(m_sevSockFd, (struct sockaddr*)&addr, &addrLength);
	if (-1 == m_clientSockFd)
	{
		LOG_INFO("accept failed err:%s", strerror(errno));
		return FAILED_ACCEPT;
	}
	return SUCCESS;
}

/** brief
 *  �������ܣ���Sokcet�ж�ȡ����
 *  ����˵����pBuffer[out] ��Socket�ж�ȡ��������
 *  	  len[in] pBuffer�ĳ���
 *  ����ֵ��ʵ�ʶ�ȡ�����ݳ���
 *       -1 ��ȡʧ��
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
 *  �������ܣ���Socket��д������
 *  ����˵����pBuffer[in] ��д�����������
 *  	  len[in] pBuffer�ĳ���
 *  ����ֵ��ʵ�ʶ�ȡ�����ݳ���
 *       -1 д��ʧ��
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
