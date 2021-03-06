/*-------------------------------------------------------------------------
 * drawElements Quality Program Helper Library
 * -------------------------------------------
 *
 * Copyright 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *//*!
 * \file
 * \brief Debug output utilities.
 *//*--------------------------------------------------------------------*/

#include "qpDebugOut.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum MessageType_e
{
	MESSAGETYPE_INFO	= 0,
	MESSAGETYPE_ERROR,

	MESSAGETYPE_LAST
} MessageType;

static void		printRaw		(MessageType type, const char* msg);
static void		printFmt		(MessageType type, const char* fmt, va_list args);
static void		exitProcess		(void);

void qpPrint (const char* message)
{
	printRaw(MESSAGETYPE_INFO, message);
}

void qpPrintf (const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printFmt(MESSAGETYPE_INFO, format, args);
	va_end(args);
}

void qpPrintv (const char* format, va_list args)
{
	printFmt(MESSAGETYPE_INFO, format, args);
}

void qpDief (const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printFmt(MESSAGETYPE_ERROR, format, args);
	va_end(args);

	exitProcess();
}

void qpDiev (const char* format, va_list args)
{
	printFmt(MESSAGETYPE_ERROR, format, args);
	exitProcess();
}

/* print() implementation. */
#if (DE_OS == DE_OS_ANDROID)

#include <android/log.h>

static android_LogPriority getLogPriority (MessageType type)
{
	switch (type)
	{
		case MESSAGETYPE_INFO:	return ANDROID_LOG_INFO;
		case MESSAGETYPE_ERROR:	return ANDROID_LOG_FATAL;
		default:				return ANDROID_LOG_DEBUG;
	}
}

void printRaw (MessageType type, const char* message)
{
	__android_log_write(getLogPriority(type), "dEQP", message);
}

void printFmt (MessageType type, const char* format, va_list args)
{
	__android_log_vprint(getLogPriority(type), "dEQP", format, args);
}

#else

static FILE* getOutFile (MessageType type)
{
	if (type == MESSAGETYPE_ERROR)
		return stderr;
	else
		return stdout;
}

void printRaw (MessageType type, const char* message)
{
	FILE* out = getOutFile(type);

	if (type == MESSAGETYPE_ERROR)
		fprintf(out, "FATAL ERROR: ");

	fputs(message, out);

	if (type == MESSAGETYPE_ERROR)
	{
		putc('\n', out);
		fflush(out);
	}
}

void printFmt (MessageType type, const char* format, va_list args)
{
	FILE* out = getOutFile(type);

	if (type == MESSAGETYPE_ERROR)
		fprintf(out, "FATAL ERROR: ");

	vfprintf(out, format, args);

	if (type == MESSAGETYPE_ERROR)
	{
		putc('\n', out);
		fflush(out);
	}
}

#endif

/* exitProcess() implementation. */
#if (DE_OS == DE_OS_WIN32)

#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static void exitProcess (void)
{
	/* Some API implementations register atexit() functions that may hang.
	   By using TerminateProcess() we can avoid calling any potentially hanging exit routines. */
	HANDLE curProc = GetCurrentProcess();
	TerminateProcess(curProc, -1);
}

#elif (DE_OS == DE_OS_IOS)

#include "deThread.h"

static void exitProcess (void)
{
	/* Since tests are in the same process as execserver, we want to give it
	   a chance to stream complete log data before terminating. */
	deSleep(5000);
	exit(-1);
}

#else

static void exitProcess (void)
{
	exit(-1);
}

#endif
