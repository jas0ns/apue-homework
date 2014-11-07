#include "CalThreadPool.h"

void *PlusRequestHandler(void *arg);
void *SubRequestHandler(void *arg);
void *MultRequestHandler(void *arg);
void *DivRequestHandler(void *arg);

CalThreadPool::CalThreadPool()
{
	pthread_mutex_init(&(this->pluslock), NULL);
}

pthread_t CalThreadPool::PlusThreadRun()
{
	pthread_t plustid;
	int err;
	err = pthread_create(&plustid, NULL, PlusRequestHandler, this);
	if (err != 0)
		cout << strerror(err) << " : plus thread create error!"
			<< endl;
	return plustid;
}

pthread_t CalThreadPool::SubThreadRun()
{
	pthread_t subtid;
	int err;
	err = pthread_create(&subtid, NULL, SubRequestHandler, NULL);
	if (err != 0)
		cout << strerror(err) << " : sub thread create error!"
			<< endl;
	return subtid;
}

pthread_t CalThreadPool::MultThreadRun()
{
	pthread_t multtid;
	int err;
	err = pthread_create(&multtid, NULL, MultRequestHandler, NULL);
	if (err != 0)
		cout << strerror(err) << " : mult thread create error!"
			<< endl;
	return multtid;
}

pthread_t CalThreadPool::DivThreadRun()
{
	pthread_t divtid;
	int err;
	err = pthread_create(&divtid, NULL, DivRequestHandler, NULL);
	if (err != 0)
		cout << strerror(err) << " : div thread create error!"
			<< endl;
	return divtid;
}

void *PlusRequestHandler(void *arg)
{
	CalThreadPool *calThreadPool = (CalThreadPool *)arg;
	while(1)
	{
		Request request = (*calThreadPool).GetPlusRequest();	
		double result = 0;
		cout << "thread" << request.qi+1 << " "<< request.x << " " << request.y << endl;
		result = request.x + request.y;
		(*calThreadPool).resultQueues[request.qi].push(result);
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

		result = request.x - request.y;
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

		result = request.x * request.y;
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

		result = request.x / request.y;
	}
}

void CalThreadPool::AddPlusRequest(Request request)
{
	pthread_mutex_lock(&pluslock);
	this->plusRequestQ.push(request);
	pthread_mutex_unlock(&pluslock);
}

void CalThreadPool::AddSubRequest(Request request)
{
	this->subRequestQ.push(request);
}

void CalThreadPool::AddMultRequest(Request request)
{
	this->multRequestQ.push(request);
}

void CalThreadPool::AddDivRequest(Request request)
{
	this->divRequestQ.push(request);
}

Request CalThreadPool::GetPlusRequest()
{
	while(this->plusRequestQ.empty()) {} 
	Request request = this->plusRequestQ.front();
	this->plusRequestQ.pop();
	return request;
}

Request CalThreadPool::GetSubRequest()
{
	Request request = this->subRequestQ.front();
	this->subRequestQ.pop();
	return request;
}

Request CalThreadPool::GetMultRequest()
{
	Request request = this->multRequestQ.front();
	this->multRequestQ.pop();
	return request;
}

Request CalThreadPool::GetDivRequest()
{
	Request request = this->divRequestQ.front();
	this->divRequestQ.pop();
	return request;
}
