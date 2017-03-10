#include "Thread.h"
#include <unistd.h>
#include <boost/bind.hpp>
#include <iostream>
using namespace std;

class Thread_test 
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

	void Test1()
	{
		while(m_Count--)
		{
			cout<<"this is a test1..."<<m_Count<<endl;
			sleep(1);
		}		
	}

	void Test2(int x)
	{
		while(m_Count--)
		{
			cout<<"this is a test2..."<<m_Count<<endl;
			sleep(1);
		}		
	}

	int m_Count;	
};

void ThreadFunc()
{
	cout<<"ThreadFunc..."<<endl;
}

void ThreadFunc2(int count)
{
	while(count--)
	{
		cout<<"ThreadFunc2..."<<endl;	
	}	
}

int main(void)
{
	Thread t1(ThreadFunc);
	Thread t2(boost::bind(ThreadFunc2,3));
	Thread_test foo(3);
	Thread t3(boost::bind(&Thread_test::Test1,&foo));
	Thread_test foo2(3);
	Thread t4(boost::bind(&Thread_test::Test2,&foo2,100));

	t1.Start();
	t2.Start();
	t3.Start();
	t4.Start();
	t1.Join();
	t2.Join();
	t3.Join();
	t4.Join();
	return 0;
}