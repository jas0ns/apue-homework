#include "CalThreadPool.h"

void *PlusRequestHandler(void *arg);
void *SubRequestHandler(void *arg);
void *MultRequestHandler(void *arg);
void *DivRequestHandler(void *arg);

CalThreadPool::CalThreadPool()
{
}

pthread_t CalThreadPool::PlusThreadRun()
{
	pthread_t plustid;
	int err;
	err = pthread_create(&plustid, NULL, PlusRequestHandler, this->plusfd);
	if (err != 0)
		cout << strerror(err) << " : plus thread create error!"
			<< endl;
	return plustid;
}

pthread_t CalThreadPool::SubThreadRun()
{
	pthread_t subtid;
	int err;
	err = pthread_create(&subtid, NULL, SubRequestHandler, this->subfd);
	if (err != 0)
		cout << strerror(err) << " : sub thread create error!"
			<< endl;
	return subtid;
}

pthread_t CalThreadPool::MultThreadRun()
{
	pthread_t multtid;
	int err;
	err = pthread_create(&multtid, NULL, MultRequestHandler, this->multfd);
	if (err != 0)
		cout << strerror(err) << " : mult thread create error!"
			<< endl;
	return multtid;
}

pthread_t CalThreadPool::DivThreadRun()
{
	pthread_t divtid;
	int err;
	err = pthread_create(&divtid, NULL, DivRequestHandler, this->divfd);
	if (err != 0)
		cout << strerror(err) << " : div thread create error!"
			<< endl;
	return divtid;
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
		if(write(request.resultPipeWfd, &result, sizeof(double)) == -1)
	 		perror("write result to pipe error");
	}
}

void *SubRequestHandler(void *arg)
{
	int subfd = *(int *)arg;
	while(1)
	{
		Request request;
		double result = 0;
		int n;
		if((n = read(subfd, &request, sizeof(Request))) == -1)
			perror("read sub pipe to x error");
		else if (n == 0)
		{
			if (close(subfd) == -1)
				perror("close sub pipe error");
			break;
		}

		result = request.x - request.y;
		if(write(request.resultPipeWfd, &result, sizeof(double)) == -1)
	 		perror("write result to pipe error");
	}
}

void *MultRequestHandler(void *arg)
{
	int multfd = *(int *)arg;
	while(1)
	{
		Request request;
		double result = 0;
		int n;
		if((n = read(multfd, &request, sizeof(Request))) == -1)
			perror("read mult pipe to x error");
		else if (n == 0)
		{
			if (close(multfd) == -1)
				perror("close mult pipe error");
			break;
		}

		result = request.x * request.y;
		if(write(request.resultPipeWfd, &result, sizeof(double)) == -1)
	 		perror("write result to pipe error");
	}
}

void *DivRequestHandler(void *arg)
{
	int divfd = *(int *)arg;
	while(1)
	{
		Request request;
		double result = 0;
		int n;
		if((n = read(divfd, &request, sizeof(Request))) == -1)
			perror("read div pipe to x error");
		else if (n == 0)
		{
			if (close(divfd) == -1)
				perror("close div pipe error");
			break;
		}

		result = request.x / request.y;
		if(write(request.resultPipeWfd, &result, sizeof(double)) == -1)
	 		perror("write result to pipe error");
	}
}

