#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <boost/function.hpp>

class Thread
{
public:
	typedef boost::function<void()> ThreadFunc;
	explicit Thread(const ThreadFunc& func);
	virtual ~Thread();

	void Start();
	void Join();
	void SetAutoDel(bool autoDel) {m_AutoDel = autoDel;};

private:
	static void* ThreadRoutine(void *arg);
	virtual void Run();

	pthread_t 	m_ThreadId;
	bool 		m_AutoDel;
	ThreadFunc  m_func;
};

#endif   // _THREAD_H_