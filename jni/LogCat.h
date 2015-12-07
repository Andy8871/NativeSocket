/*
 * LogCat.h
 *
 *  Created on: 2015-12-4
 *      Author: andy
 */

#ifndef LOGCAT_H_
#define LOGCAT_H_

#include <android/log.h>

#define LOG_LEVEL_VERBOSE	1
#define LOG_LEVEL_DEBUG		2
#define LOG_LEVEL_INFO 		3
#define LOG_LEVEL_WARNING	4
#define LOG_LEVEL_ERROR		5
#define LOG_LEVEL_FATAL		6
#define LOG_LEVEL_SILENT	7

#ifndef LOG_TAG
#define LOG_TAG		__FILE__
#endif

#ifndef LOG_LEVEL
#define LOG_LEVEL	LOG_LEVEL_VERBOSE
#endif

#define LOG_NOOP (void)0

#define LOG_PRINT(level, fmt, ...)			\
	__android_log_print(level, LOG_TAG, "(%s:%u) %s:" fmt, \
			__FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)


#if LOG_LEVEL <= LOG_LEVEL_VERBOSE
#define LOG_VERBOSE(fmt, ...)				\
	LOG_PRINT(ANDROID_LOG_VERBOSE, fmt, ##__VA_ARGS__)
#else
#define LOG_VERBOSE(...)	LOG_NOOP
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(fmt, ...)				\
	LOG_PRINT(ANDROID_LOG_DEBUG, fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(...)	LOG_NOOP
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(fmt, ...)				\
	LOG_PRINT(ANDROID_LOG_INFO, fmt, ##__VA_ARGS__)
#else
#define LOG_INFO(...)	LOG_NOOP
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
#define LOG_WARNING(fmt, ...)				\
	LOG_PRINT(ANDROID_LOG_WARN, fmt, ##__VA_ARGS__)
#else
#define LOG_WARNING(...)	LOG_NOOP
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(fmt, ...)				\
	LOG_PRINT(ANDROID_LOG_ERROR, fmt, ##__VA_ARGS__)
#else
#define LOG_ERROR(...)	LOG_NOOP
#endif

#if LOG_LEVEL <= LOG_LEVEL_FATAL
#define LOG_FATAL(fmt, ...)				\
	LOG_PRINT(ANDROID_LOG_FATAL, fmt, ##__VA_ARGS__)
#else
#define LOG_FATAL(...)	LOG_NOOP
#endif

#if LOG_LEVEL <= LOG_LEVEL_SILENT
#define LOG_SILENT(fmt, ...)				\
	LOG_PRINT(ANDROID_LOG_SILENT, fmt, ##__VA_ARGS__)
#else
#define LOG_SILENT(...)	LOG_NOOP
#endif

#endif /* LOGCAT_H_ */
