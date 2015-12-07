/*
 * NativeClient.cpp
 *
 *  Created on: 2015-12-4
 *      Author: andy
 */
#include <jni.h>
#include <sys/socket.h>
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
	/* ��ȡJNI�����Ļ��� */
	if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		return JNI_ERR;

	/* ���Ҷ���ԭ��������Java�� */
	jclass clazz = env->FindClass("com/vagrenat/nativesocket/Client");

	/*jclass clazzException = env->FindClass("java/lang/RuntimeException");
		env->ThrowNew(clazzException, __FILE__);
*/
	if (NULL == clazz)
		return JNI_ERR;

	/* ע��ԭ��������Java����� */
	if (env->RegisterNatives(clazz, gMethods, gMethods_Len) != JNI_OK)
		return JNI_ERR;

	return JNI_VERSION_1_4;
}

/**
 * brief
 * ����˵�������ӵ�Socket�����
 * ����˵����ipAddr[in] ����IP��ַ
 * 		 port[in] �������˿�
 */
jboolean JNICALL Connect
  (JNIEnv * env, jobject obj, jstring ipAddr, jstring port)
{
	//LOG_DEBUG("Connect");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servAddr;
	connect(sockfd, (struct sockaddr*)&servAddr, (int)sizeof(servAddr));
	return false;
}

/**
 * brief
 * �������ܣ��Ͽ��ͻ�������
 * ����˵������
 * ����ֵ����
 */
void JNICALL Disconnect
  (JNIEnv * env, jobject obj)
{

}

/**
 * brief
 * �������ܣ� ��Socket��ȡ����
 * ����˵����len[in] ָ���Ķ�ȡ���ݳ���
 * ����ֵ����ȡ����������
 */
jbyteArray JNICALL Recv
  (JNIEnv *env, jobject obj, jint len)
{
	return NULL;
}

/**
 * brief
 * �������ܣ���Socketд����
 * ����˵����buff[in] ��Ҫд�����������
 *		 len[in] buff�ĳ���
 * ����ֵ��ʵ��д����������ݳ���
 */
jint JNICALL Send
  (JNIEnv *, jobject, jbyteArray buff, jint len)
{
	return 0;
}



