/*-------------------------------------------------------------------------
 * drawElements Thread Library
 * ---------------------------
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
 * \brief Unix implementation of thread management.
 *//*--------------------------------------------------------------------*/

#include "deThread.h"

#if (DE_OS == DE_OS_UNIX || DE_OS == DE_OS_OSX || DE_OS == DE_OS_ANDROID || DE_OS == DE_OS_SYMBIAN || DE_OS == DE_OS_IOS)

#include "deMemory.h"

#if !defined(_XOPEN_SOURCE) || (_XOPEN_SOURCE < 500)
#	error You are using too old posix API!
#endif

#include <unistd.h>
#include <pthread.h>
#include <sched.h>

typedef struct Thread_s
{
	pthread_t		thread;
	deThreadFunc	func;
	void*			arg;
} Thread;

DE_STATIC_ASSERT(sizeof(deThread) >= sizeof(Thread*));

static void* startThread (void* entryPtr)
{
	Thread*			thread	= (Thread*)entryPtr;
	deThreadFunc	func	= thread->func;
	void*			arg		= thread->arg;

	/* Start actual thread. */
	func(arg);

	return DE_NULL;
}

deThread deThread_create (deThreadFunc func, void* arg, const deThreadAttributes* attributes)
{
	pthread_attr_t	attr;
	Thread*			thread	= (Thread*)deCalloc(sizeof(Thread));

	if (!thread)
		return 0;

	thread->func	= func;
	thread->arg		= arg;

	if (pthread_attr_init(&attr) != 0)
	{
		deFree(thread);
		return 0;
	}

	/* \todo [2009-11-12 pyry] Map attributes. */
	DE_UNREF(attributes);

	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) != 0)
	{
		pthread_attr_destroy(&attr);
		deFree(thread);
		return 0;
	}

	if (pthread_create(&thread->thread, &attr, startThread, thread) != 0)
	{
		pthread_attr_destroy(&attr);
		deFree(thread);
		return 0;
	}
	DE_ASSERT(thread->thread);

	pthread_attr_destroy(&attr);

	return (deThread)thread;
}

deBool deThread_join (deThread threadptr)
{
	Thread*		thread	= (Thread*)threadptr;
	int			ret;

	DE_ASSERT(thread->thread);
	ret = pthread_join(thread->thread, DE_NULL);

	/* If join fails for some reason, at least mark as detached. */
	if (ret != 0)
		pthread_detach(thread->thread);

	/* Thread is no longer valid as far as we are concerned. */
	thread->thread = 0;

	return (ret == 0);
}

void deThread_destroy (deThread threadptr)
{
	Thread* thread = (Thread*)threadptr;

	if (thread->thread)
	{
		/* Not joined, detach. */
		int ret = pthread_detach(thread->thread);
		DE_ASSERT(ret == 0);
		DE_UNREF(ret);
	}

	deFree(thread);
}

void deSleep (deUint32 milliseconds)
{
	/* Maximum value for usleep is 10^6. */
	deUint32 seconds = milliseconds / 1000;

	milliseconds = milliseconds - seconds * 1000;

	if (seconds > 0)
		sleep(seconds);

	usleep((useconds_t)milliseconds * (useconds_t)1000);
}

void deYield (void)
{
	sched_yield();
}

#endif /* DE_OS */
