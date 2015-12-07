/*
 * NativeException.h
 *
 *  Created on: 2015-12-5
 *      Author: andy
 */

#ifndef NATIVEEXCEPTION_H_
#define NATIVEEXCEPTION_H_

#include <string.h>
#include <errno.h>

void ThrowException(JNIEnv* env, const char* className, const char* message);
void ThrowErrnoException(JNIEnv* env, const char* className, int errnum);
#endif /* NATIVEEXCEPTION_H_ */
