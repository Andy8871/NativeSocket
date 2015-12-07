/*
 * Diagnose.cpp
 *
 *  Created on: 2015-12-5
 *      Author: andy
 */

#include <jni.h>
#include "NativeException.h"
#ifndef NULL
#define NULL 0
#endif

void JNICALL Run(JNIEnv *, jobject);
void JNICALL Exit(JNIEnv *, jobject);

static CommWithDisplayBase comm;

/* Java������ӿ�ָ�빩ȫ�ֵ��� */
static JavaVM* gVM = NULL;

/* Java layer��Diagnose�����ȫ������ */
static jobject gObj = NULL;

static JNINativeMethod gMethods =
{
		{"run", "()V", (void*)Run},
		{"exit", "()V", (void*)Exit}
};

jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	gVM = vm;
	JNIEnv* env = NULL;
	if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		return JNI_ERR;

	jclass clazz = env->FindClass("com/vagrenat/nativesokcet/Diagnose");
	if (NULL == clazz)
		ThrowErrnoException(env, "java/io/IOException", errno);

	/* ע��ԭ������ */
	if (env->RegisterNatives(clazz, &gMethods, (int)(sizeof(gMethods) / sizeof(gMethods[0]))) != JNI_OK)
		ThrowErrnoException(env, "java/io/IOException", errno);

	/* �ͷ�ԭ���������� */
	env->DeleteLocalRef(clazz);
	return JNI_VERSION_1_4;
}


/** brief
 * �������ܣ�������ϳ��򣬳�ʼ��ȫ�ֶ�������
 * ����˵������
 * ����ֵ����
 */
void JNICALL Run(JNIEnv *env, jobject obj)
{
	if (NULL == gObj)
	{
		gObj = env->NewGlobalRef(obj);
		if (NULL == gObj)
			return;
	}
	comm.Init();
}

/** brief
 * �������ܣ��˳���ϳ�������ȫ�ֶ�������
 * ����˵������
 * ����ֵ����
 */
void JNICALL Exit(JNIEnv * env, jobject obj)
{
	if (NULL != gObj)
	{
		env->DeleteGlobalRef(gObj);
		gObj = NULL;
	}
	comm.free();
}




