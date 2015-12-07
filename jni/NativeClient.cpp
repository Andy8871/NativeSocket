/*
 * NativeClient.cpp
 *
 *  Created on: 2015-12-4
 *      Author: andy
 */
#include <jni.h>
#include <sys/socket.h>
#include <sys/endian.h>
#include <arpa/inet.h>
#include "LogCat.h"
#ifndef NULL
#define NULL 0
#endif

JNIEXPORT jboolean JNICALL Connect(JNIEnv *, jobject, jstring, jstring);
JNIEXPORT void JNICALL Disconnect(JNIEnv *, jobject);
JNIEXPORT jbyteArray JNICALL Recv(JNIEnv *, jobject, jint);
JNIEXPORT jint JNICALL Send(JNIEnv *, jobject, jbyteArray, jint);


static JNINativeMethod gMethods[] =
{
	{"connect", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)Connect},
	{"disconnect", "()V", (void*)Disconnect},
	{"recv", "(I)[B", (void*)Recv},
	{"send", "([BI)I", (void*)Send}
};

jint gMethods_Len = sizeof(gMethods) / sizeof(gMethods[0]);



static int sockfd = -1;

jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	LOG_DEBUG("JNI_OnLoad Methods size=%d", gMethods_Len);
	JNIEnv* env = NULL;
	/* 获取JNI上下文环境 */
	if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		return JNI_ERR;

	/* 查找定义原生方法的Java类 */
	jclass clazz = env->FindClass("com/vagrenat/nativesocket/Client");

	/*jclass clazzException = env->FindClass("java/lang/RuntimeException");
		env->ThrowNew(clazzException, __FILE__);
*/
	if (NULL == clazz)
		return JNI_ERR;

	/* 注册原生方法到Java虚拟机 */
	if (env->RegisterNatives(clazz, gMethods, gMethods_Len) != JNI_OK)
		return JNI_ERR;

	return JNI_VERSION_1_4;
}

/**
 * brief
 * 函数说明：连接到Socket服务端
 * 参数说明：ipAddr[in] 请求IP地址
 * 		 port[in] 请求服务端口
 */
jboolean JNICALL Connect
  (JNIEnv * env, jobject obj, jstring ipAddr, jstring port)
{
	//LOG_DEBUG("Connect");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		LOG_DEBUG("Client failed to socket ...");
		return false;
	}

	struct sockaddr_in servAddr;
	memset((void*)&servAddr, 0, (int)sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9527);
	if (inet_pton(AF_INET, "127.0.0.1", (void*)&servAddr) < 0)
	{
		LOG_DEBUG("Client failed to parse IP Address ...");
		return false;
	}
	if (connect(sockfd, (struct sockaddr*)&servAddr, (int)sizeof(servAddr)) < 0)
	{
		LOG_DEBUG("Client failed to connect server ...");
		return false;
	}
	return true;
}

/**
 * brief
 * 函数功能：断开客户端连接
 * 参数说明：无
 * 返回值：无
 */
void JNICALL Disconnect
  (JNIEnv * env, jobject obj)
{
	if (-1 != sockfd)
	{
		close(sockfd);
	}
}

/**
 * brief
 * 函数功能： 从Socket读取数据
 * 参数说明：len[in] 指定的读取数据长度
 * 返回值：读取的数据内容
 */
jbyteArray JNICALL Recv
  (JNIEnv *env, jobject obj, jint len)
{
	return NULL;
}

/**
 * brief
 * 函数功能：向Socket写数据
 * 参数说明：buff[in] 需要写入的数据内容
 *		 len[in] buff的长度
 * 返回值：实际写入的数据内容长度
 */
jint JNICALL Send
  (JNIEnv *, jobject, jbyteArray buff, jint len)
{
	return 0;
}



