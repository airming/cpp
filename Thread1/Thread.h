#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

class Thread
{
public:
	Thread();
	virtual ~Thread();

	void Start();
	void Join();
	void SetAutoDel(bool autoDel) {m_AutoDel = autoDel;};

private:
	static void* ThreadRoutine(void *arg);
	virtual void Run() = 0;

	pthread_t 	m_ThreadId;
	bool 		m_AutoDel;
};

#endif   // _THREAD_H_