/*
 * CommWithDisplayBase.h
 *
 *  Created on: 2015-12-5
 *      Author: andy
 */

#ifndef COMMWITHDISPLAYBASE_H_
#define COMMWITHDISPLAYBASE_H_

class CommWithDisplayBase{
public:
	const static int SUCCESS = 0;
	const static int FAILED_NEW_RECV_BUFF = 1;
	const static int FAILED_NEW_SEND_BUFF = 2;
	const static int FAILED_SCOKET = 3;
	const static int FAILED_BIND = 4;
	const static int FAILED_LISTEN = 5;
	const static int FAILED_ACCEPT = 6;
public:
	CommWithDisplayBase();
	virtual ~CommWithDisplayBase();
public:
	int Init();
	int SendData(const char* pBuffer, int len);
	int GetData(char* pBuffer, int len);
	void free();
private:
	int m_sevSockFd;
	int m_clientSockFd;
	char* m_pRecvBuff;
	char* m_pSendBuff;
private:
	const static int PORT = 9527;
	const static int MAX_RECV_BUFFER_LENGTH = 0xFF;
	const static int MAX_SEND_BUFFER_LENGTH = 0xFFFF;
};


#endif /* COMMWITHDISPLAYBASE_H_ */
