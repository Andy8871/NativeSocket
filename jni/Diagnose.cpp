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

/* Java虚拟机接口指针供全局调用 */
static JavaVM* gVM = NULL;

/* Java layer中Diagnose对象的全局引用 */
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

	/* 注册原生函数 */
	if (env->RegisterNatives(clazz, &gMethods, (int)(sizeof(gMethods) / sizeof(gMethods[0]))) != JNI_OK)
		ThrowErrnoException(env, "java/io/IOException", errno);

	/* 释放原生对象引用 */
	env->DeleteLocalRef(clazz);
	return JNI_VERSION_1_4;
}


/** brief
 * 函数功能：启动诊断程序，初始化全局对象引用
 * 参数说明：无
 * 返回值：无
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
 * 函数功能：退出诊断程序，清理全局对象引用
 * 参数说明：无
 * 返回值：无
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




