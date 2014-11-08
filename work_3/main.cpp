#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "CalThreadPool.h"

#define PLUSTHREADNUMBER 2
#define SUBTHREADNUMBER 1
#define MULTTHREADNUMBER 1
#define DIVTHREADNUMBER 1
#define QUEUENUMBER PLUSTHREADNUMBER+SUBTHREADNUMBER+MULTTHREADNUMBER+DIVTHREADNUMBER

using namespace std;

void *PullPlusRequest(void *arg);
void *PullSubRequest(void *arg);
void *PullMultRequest(void *arg);
void *PullDivRequest(void *arg);

class Args {
public:
	Args(CalThreadPool *ctp, queue<double> *rq, int qi)
		:ctp(ctp),rq(rq),qi(qi){}
	
	CalThreadPool *ctp;
	queue<double> *rq;
	int qi;
};

int main(int argc, char **argv)
{
	CalThreadPool calThreadPool;// include create request pipe
	queue<double> resultQueues[QUEUENUMBER];
	calThreadPool.resultQueues = resultQueues;
	
	pthread_t plustid = calThreadPool.PlusThreadRun(); // plus service thread
	pthread_t subtid = calThreadPool.SubThreadRun(); // sub service thread
	pthread_t multtid = calThreadPool.MultThreadRun(); // mult service thread
	pthread_t divtid = calThreadPool.DivThreadRun(); // div service thread

	pthread_t plusReqtids[PLUSTHREADNUMBER]; // plus request thread
	pthread_t subReqtids[SUBTHREADNUMBER]; // sub request thread
	pthread_t multReqtids[MULTTHREADNUMBER]; // mult request thread
	pthread_t divReqtids[DIVTHREADNUMBER]; // div request thread

	int qi = 0;
	for (int i=0; i<PLUSTHREADNUMBER; i++)
	{
		int err;
		Args *args = new Args(&calThreadPool, resultQueues, qi++);
		err = pthread_create(&(plusReqtids[i]), NULL, PullPlusRequest, args);
		if (err != 0)
			cout << strerror(err) 
				<< " : plus request thread create error" << endl;
	}

	for (int i=0; i<SUBTHREADNUMBER; i++)
	{
		int err;
		Args *args = new Args(&calThreadPool, resultQueues, qi++);
		err = pthread_create(&(subReqtids[i]), NULL, PullSubRequest, args);
		if (err != 0)
			cout << strerror(err) 
				<< " : sub request thread create error" << endl;
	}

	for (int i=0; i<MULTTHREADNUMBER; i++)
	{
		int err;
		Args *args = new Args(&calThreadPool, resultQueues, qi++);
		err = pthread_create(&(multReqtids[i]), NULL, PullMultRequest, args);
		if (err != 0)
			cout << strerror(err) 
				<< " : mult request thread create error" << endl;
	}

	for (int i=0; i<DIVTHREADNUMBER; i++)
	{
		int err;
		Args *args = new Args(&calThreadPool, resultQueues, qi++);
		err = pthread_create(&(divReqtids[i]), NULL, PullDivRequest, args);
		if (err != 0)
			cout << strerror(err) 
				<< " : div request thread create error" << endl;
	}

	for (int i=0; i<PLUSTHREADNUMBER; i++)
		pthread_join(plusReqtids[i], NULL);
	for (int i=0; i<SUBTHREADNUMBER; i++)
		pthread_join(subReqtids[i], NULL);
	for (int i=0; i<MULTTHREADNUMBER; i++)
		pthread_join(multReqtids[i], NULL);
	for (int i=0; i<DIVTHREADNUMBER; i++)
		pthread_join(divReqtids[i], NULL);
	
	/*pthread_join(plustid, NULL);
	pthread_join(subtid, NULL); 
	pthread_join(multtid, NULL); 
	pthread_join(divtid, NULL);      
	*/	
	return 0;
}

void *PullPlusRequest(void *args)
{
	Args *_args = (Args *)args;
	cout << "new plus request thread run, NO:" << _args->qi << endl; 
	CalThreadPool *calThreadPool = _args->ctp;
	queue<double> *requestQueues = _args->rq;
	int qi = _args->qi;
	delete _args;
	queue<double> *q = &(requestQueues[qi]);
	for(int i=0; i<1000; i++)
	{
		Request request(i+2, i+1, qi);
		(*calThreadPool).AddPlusRequest(request);
		while ((*q).empty()) {}
		double result = (*q).front();
		(*q).pop();
	}
}

void *PullSubRequest(void *args)
{
	Args *_args = (Args *)args;
	cout << "new sub request thread run, NO:" << _args->qi << endl; 
	CalThreadPool *calThreadPool = _args->ctp;
	queue<double> *requestQueues = _args->rq;
	int qi = _args->qi;
	delete _args;
	queue<double> *q = &(requestQueues[qi]);
	for(int i=0; i<1000; i++)
	{
		Request request(i+2, i+1, qi);
		(*calThreadPool).AddSubRequest(request);
		while ((*q).empty()) {}
		double result = (*q).front();
		(*q).pop();
	}
}

void *PullMultRequest(void *args)
{
	Args *_args = (Args *)args;
	cout << "new mult request thread run, NO:" << _args->qi << endl; 
	CalThreadPool *calThreadPool = _args->ctp;
	queue<double> *requestQueues = _args->rq;
	int qi = _args->qi;
	delete _args;
	queue<double> *q = &(requestQueues[qi]);
	for(int i=0; i<1000; i++)
	{
		Request request(i+2, i+1, qi);
		(*calThreadPool).AddMultRequest(request);
		while ((*q).empty()) {}
		double result = (*q).front();
		(*q).pop();
	}
}

void *PullDivRequest(void *args)
{
	Args *_args = (Args *)args;
	cout << "new div request thread run, NO:" << _args->qi << endl; 
	CalThreadPool *calThreadPool = _args->ctp;
	queue<double> *requestQueues = _args->rq;
	int qi = _args->qi;
	delete _args;
	queue<double> *q = &(requestQueues[qi]);
	for(int i=0; i<1000; i++)
	{
		Request request(i+2, i+1, qi);
		(*calThreadPool).AddDivRequest(request);
		while ((*q).empty()) {}
		double result = (*q).front();
		(*q).pop();
	}
}



