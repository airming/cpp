#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

#define ERR_EXIT(m) \
		do \
		{\
			perror(m);\
			exit(EXIT_FAILURE);\
		}while(0)

#define SERVER_PORT 5188

typedef vector<struct pollfd> PollFdList;

int main(void){
	signal(SIGPIPE, SIG_IGN);	//信号忽略
	signal(SIGCHLD, SIG_IGN);

	int listenfd;
	if ((listenfd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP)) < 0)
	{
		ERR_EXIT("create listen socket error");
	}

	struct sockaddr_in servaddr;
	memset(&servaddr, 0 , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		ERR_EXIT("setsockopt error");
	}

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		ERR_EXIT("bind error");
	}
	if (listen(listenfd, SOMAXCONN) < 0)
	{
		ERR_EXIT("listen error");
	}

	struct pollfd pfd;
	pfd.fd = listenfd;
	pfd.events = POLLIN;
	PollFdList pollfds;
	pollfds.push_back(pfd);
	int nready;
	struct sockaddr_in peeraddr;
	socklen_t peerlen;
	int connfd;

	while(true){
		nready = poll(&*pollfds.begin(), pollfds.size(), -1);
		if (nready == -1)
		{
			if (errno == EINTR)
			{
				continue;
			}
			ERR_EXIT("poll error");
		}
		if (nready == 0)  // nothing happended
		{
			continue;
		}

		if (pollfds[0].revents & POLLIN)
		{
			peerlen = sizeof(peeraddr);
			connfd = accept4(listenfd, (struct sockaddr*)&peeraddr, &peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
			if (connfd == -1)
			{
				ERR_EXIT("accpet4 error");
			}
			pfd.fd = connfd;
			pfd.events = POLLIN;
			pfd.revents = 0;
			pollfds.push_back(pfd);
			--nready;

			cout<<"ip ="<<inet_ntoa(peeraddr.sin_addr)<<" port="<<ntohs(peeraddr.sin_port)<<endl;
			if (nready == 0)
			{
				continue;
			}
		}

		for (PollFdList::iterator it = pollfds.begin() + 1; it < pollfds.end() && nready > 0; ++it)
		{
			if (it->revents & POLLIN)
			{
				--nready;
				connfd = it->fd;
				char buf[1024] = {0};
				int ret = read(connfd, buf, 1024);
				if (ret == 0)
				{
					cout<<"client close"<<endl;
					it = pollfds.erase(it);
					--it;
					close(connfd);
					continue;
				}
				cout<<buf;
				write(connfd, buf, strlen(buf));
			}
		}
	}

	return 0;
}
