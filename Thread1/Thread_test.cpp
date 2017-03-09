#include "Thread.h"
#include <unistd.h>
#include <iostream>
using namespace std;

class Thread_test : public Thread
{
public:
	Thread_test(int count) :m_Count(count)
	{
		cout<<"Thread_test..."<<endl;
	}

	~Thread_test()
	{
		cout<<"~Thread_test..."<<endl;
	}

private:
	void Run()
	{
		while(m_Count--)
		{
			cout<<"this is a test..."<<m_Count<<endl;
			sleep(1);
		}		
	}

	int m_Count;	
};

int main(void)
{
	Thread_test *t = new Thread_test(5);
	t->SetAutoDel(true);
	t->Start();
	t->Join();
	
	while(1)
	{

	}
}