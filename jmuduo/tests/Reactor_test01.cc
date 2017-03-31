#include <muduo/net/EventLoop.h>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

void threadFunc(){
	printf("threadFunc(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());

	EventLoop loop;
	loop.loop();
}

int main(int argc, char const *argv[])
{
	printf("main(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());

	EventLoop loop;

	Thread t(threadFunc);
	t.start();
	t.join();

	loop.loop();

	return 0;
}