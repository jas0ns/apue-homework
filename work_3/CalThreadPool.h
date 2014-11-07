#ifndef CALTHREADPOOL_H
#define CALTHREADPOOL_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

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
	
private:
};

#endif
