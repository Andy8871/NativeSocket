/*
 * NativeException.cpp
 *
 *  Created on: 2015-12-5
 *      Author: andy
 */
#include "NativeException.h"
#ifndef NULL
#define NULL 0
#endif

/* 异常消息字符串的最大长度 */
#define MAX_EXCEPTION_MSG_LENGTH	256

/**brief
 *
 * 函数功能：用给定的异常类和异常消息向Java Layer发送异常消息
 * 参数说明：env[in] JNIEnv接口
 * 		 className[in] Java Layer的异常类名
 * 		 message[in] 抛出的异常消息
 */
static void ThrowException(JNIEnv* env, const char* className,
		const char* message) {
	/* 获取异常类 */
	jclass clazz = env->FindClass(className);

	if (NULL != clazz) {
		/* 抛出异常 */
		env->ThrowNew(clazz, message);

		/* 释放原生类的引用 */
		env->DeleteLocalRef(clazz);
	}
}


/**brief
 *
 * 函数功能：用给定的异常类和给定的错误代码向Java Layer发送异常消息
 * 参数说明：env[in] JNIEnv接口
 * 		 className[in] Java Layer的异常类名
 * 		 errno[in] 抛出的错误代码
 */
static void ThrowErrnoException(JNIEnv* env, const char* className,
		int errnum) {
	char buffer[MAX_EXCEPTION_MSG_LENGTH];

	/* 获取错误代码消息 */
	if (-1 == strerror_r(errnum, buffer, MAX_EXCEPTION_MSG_LENGTH)) {
		strerror_r(errno, buffer, MAX_EXCEPTION_MSG_LENGTH);
	}
	ThrowException(env, className, buffer);
}


