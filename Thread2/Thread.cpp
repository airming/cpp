#include "Thread.h"

#include <iostream>
using namespace std;

Thread::Thread(const ThreadFunc& func) : m_AutoDel(false), m_func(func)
{
	cout<<"Thread..."<<endl;
}

Thread::~Thread()
{
	cout<<"~Thread..."<<endl;
}

void Thread::Start()
{
	pthread_create(&m_ThreadId, NULL, ThreadRoutine, this);
}

void Thread::Join()
{
	//prevent main thread exit
	pthread_join(m_ThreadId, NULL);
}

void* Thread::ThreadRoutine(void* arg)
{
	Thread* pThread = static_cast<Thread*>(arg);
	pThread->Run();
	if (pThread->m_AutoDel)
	{		
		delete pThread;
	}

	return NULL;
}

void Thread::Run()
{
	m_func();
}