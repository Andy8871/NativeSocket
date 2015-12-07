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

/* �쳣��Ϣ�ַ�������󳤶� */
#define MAX_EXCEPTION_MSG_LENGTH	256

/**brief
 *
 * �������ܣ��ø������쳣����쳣��Ϣ��Java Layer�����쳣��Ϣ
 * ����˵����env[in] JNIEnv�ӿ�
 * 		 className[in] Java Layer���쳣����
 * 		 message[in] �׳����쳣��Ϣ
 */
static void ThrowException(JNIEnv* env, const char* className,
		const char* message) {
	/* ��ȡ�쳣�� */
	jclass clazz = env->FindClass(className);

	if (NULL != clazz) {
		/* �׳��쳣 */
		env->ThrowNew(clazz, message);

		/* �ͷ�ԭ��������� */
		env->DeleteLocalRef(clazz);
	}
}


/**brief
 *
 * �������ܣ��ø������쳣��͸����Ĵ��������Java Layer�����쳣��Ϣ
 * ����˵����env[in] JNIEnv�ӿ�
 * 		 className[in] Java Layer���쳣����
 * 		 errno[in] �׳��Ĵ������
 */
static void ThrowErrnoException(JNIEnv* env, const char* className,
		int errnum) {
	char buffer[MAX_EXCEPTION_MSG_LENGTH];

	/* ��ȡ���������Ϣ */
	if (-1 == strerror_r(errnum, buffer, MAX_EXCEPTION_MSG_LENGTH)) {
		strerror_r(errno, buffer, MAX_EXCEPTION_MSG_LENGTH);
	}
	ThrowException(env, className, buffer);
}


