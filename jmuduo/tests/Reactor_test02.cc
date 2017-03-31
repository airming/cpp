#include <muduo/net/EventLoop.h>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

EventLoop* g_loop = NULL;

void threadFunc(){
	printf("threadFunc(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());	
	g_loop->loop();
}

int main(int argc, char const *argv[])
{
	printf("main(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());

	EventLoop loop;
	g_loop = &loop;
	Thread t(threadFunc);
	t.start();
	t.join();

	return 0;
}