#include "CalThreadPool.h"

void *PlusRequestHandler(void *arg);

CalThreadPool::CalThreadPool()
{
	if (pipe(plusfd) == -1) perror("create plus pipe error");
	if (pipe(subfd) == -1) perror("create sub pipe error");
	if (pipe(multfd) == -1) perror("create mult pipe error");
	if (pipe(divfd) == -1) perror("create div pipe error");
}

void CalThreadPool::PlusThreadRun()
{
	pthread_t tid;
	int err;
	err = pthread_create(&tid, NULL, PlusRequestHandler, this->plusfd);
	if (err != 0)
		cout << strerror(err) << " : plus thread create error!"
			<< endl;
}

int	CalThreadPool::GetPlusPipeWfd()
{
	return this->plusfd[1];
}

void *PlusRequestHandler(void *arg)
{
	int plusfd = *(int *)arg;
	while(1)
	{
		Request request;
		double result = 0;
		int n;
		if((n = read(plusfd, &request, sizeof(Request))) == -1)
			perror("read plus pipe to x error");
		else if (n == 0)
		{
			if (close(plusfd) == -1)
				perror("close plue pipe error");
			break;
		}

		result = request.x + request.y;
		cout << "receive request: x = " 
			<< request.x << " y = " << request.y << endl;
		
		if(write(request.resultPipeWfd, &result, sizeof(double)) == -1)
	 		perror("write result to pipe error");
	}
}

void CalThreadPool::ClosePipeWPort()
{
	if (close(plusfd[1]) == -1) 
		perror("close plus request pipe write port error");
	if (close(subfd[1]) == -1) 
		perror("close sub request pipe write port error");
	if (close(multfd[1]) == -1) 
		perror("close mult request pipe write port error");
	if (close(divfd[1]) == -1) 
		perror("close div request pipe write port error");
}

void CalThreadPool::ClosePipeRPort()
{
	if (close(plusfd[0]) == -1) 
		perror("close plus request pipe read port error");
	if (close(subfd[0]) == -1) 
		perror("close sub request pipe read port error");
	if (close(multfd[0]) == -1) 
		perror("close mult request pipe read port error");
	if (close(divfd[0]) == -1) 
		perror("close div request pipe read port error");
}
