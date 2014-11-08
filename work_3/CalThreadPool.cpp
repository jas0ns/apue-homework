#include "CalThreadPool.h"

void *PlusRequestHandler(void *arg);
void *SubRequestHandler(void *arg);
void *MultRequestHandler(void *arg);
void *DivRequestHandler(void *arg);

CalThreadPool::CalThreadPool()
{
	pthread_mutex_init(&(this->pluslock), NULL);
	pthread_mutex_init(&(this->sublock), NULL);
	pthread_mutex_init(&(this->multlock), NULL);
	pthread_mutex_init(&(this->divlock), NULL);
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
	err = pthread_create(&subtid, NULL, SubRequestHandler, this);
	if (err != 0)
		cout << strerror(err) << " : sub thread create error!"
			<< endl;
	return subtid;
}

pthread_t CalThreadPool::MultThreadRun()
{
	pthread_t multtid;
	int err;
	err = pthread_create(&multtid, NULL, MultRequestHandler, this);
	if (err != 0)
		cout << strerror(err) << " : mult thread create error!"
			<< endl;
	return multtid;
}

pthread_t CalThreadPool::DivThreadRun()
{
	pthread_t divtid;
	int err;
	err = pthread_create(&divtid, NULL, DivRequestHandler, this);
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
//		cout << "plus thread" << request.qi+1 << " "<< request.x << " " << request.y << endl;
		result = request.x + request.y;
		(*calThreadPool).resultQueues[request.qi].push(result);
	}
}

void *SubRequestHandler(void *arg)
{
	CalThreadPool *calThreadPool = (CalThreadPool *)arg;
	while(1)
	{
		Request request = (*calThreadPool).GetSubRequest();	
		double result = 0;
//		cout << "sub thread" << request.qi+1 << " "<< request.x << " " << request.y << endl;
		result = request.x - request.y;
		(*calThreadPool).resultQueues[request.qi].push(result);
	}
}

void *MultRequestHandler(void *arg)
{
	CalThreadPool *calThreadPool = (CalThreadPool *)arg;
	while(1)
	{
		Request request = (*calThreadPool).GetMultRequest();	
		double result = 0;
//		cout << "mult thread" << request.qi+1 << " "<< request.x << " " << request.y << endl;
		result = request.x * request.y;
		(*calThreadPool).resultQueues[request.qi].push(result);
	}
}

void *DivRequestHandler(void *arg)
{
	CalThreadPool *calThreadPool = (CalThreadPool *)arg;
	while(1)
	{
		Request request = (*calThreadPool).GetDivRequest();	
		double result = 0;
//		cout << "div thread" << request.qi+1 << " "<< request.x << " " << request.y << endl;
		result = request.x / request.y;
		(*calThreadPool).resultQueues[request.qi].push(result);
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
	pthread_mutex_lock(&sublock);
	this->subRequestQ.push(request);
	pthread_mutex_unlock(&sublock);
}

void CalThreadPool::AddMultRequest(Request request)
{
	pthread_mutex_lock(&multlock);
	this->multRequestQ.push(request);
	pthread_mutex_unlock(&multlock);
}

void CalThreadPool::AddDivRequest(Request request)
{
	pthread_mutex_lock(&divlock);
	this->divRequestQ.push(request);
	pthread_mutex_unlock(&divlock);
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
	while(this->subRequestQ.empty()) {} 
	Request request = this->subRequestQ.front();
	this->subRequestQ.pop();
	return request;
}

Request CalThreadPool::GetMultRequest()
{
	while(this->multRequestQ.empty()) {} 
	Request request = this->multRequestQ.front();
	this->multRequestQ.pop();
	return request;
}

Request CalThreadPool::GetDivRequest()
{
	while(this->divRequestQ.empty()) {} 
	Request request = this->divRequestQ.front();
	this->divRequestQ.pop();
	return request;
}
