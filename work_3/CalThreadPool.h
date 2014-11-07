#ifndef CALTHREADPOOL_H
#define CALTHREADPOOL_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <queue>

#include "Request.h"
using namespace std;

#define MAXNUM_RESULTPIPE 5

class CalThreadPool {
public:
	CalThreadPool();

	pthread_t PlusThreadRun();
	pthread_t SubThreadRun();
	pthread_t MultThreadRun();
	pthread_t DivThreadRun();
	
	void AddPlusRequest(Request);
	void AddSubRequest(Request);
	void AddMultRequest(Request);
	void AddDivRequest(Request);
	
	Request GetPlusRequest();
	Request GetSubRequest();
	Request GetMultRequest();
	Request GetDivRequest();
	
	queue<double> *resultQueues;
	pthread_mutex_t pluslock;
	pthread_mutex_t sublock;
	pthread_mutex_t multlock;
	pthread_mutex_t divlock;

private:
	queue<Request> plusRequestQ;
	queue<Request> subRequestQ;
	queue<Request> multRequestQ;
	queue<Request> divRequestQ;

};

#endif
