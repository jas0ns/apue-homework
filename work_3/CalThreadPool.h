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

	void PlusThreadRun();

	int GetPlusPipeWfd();
	int GetSubPipeWfd();
	int GetMultPipeWfd();
	int GetDivPipeWfd();


private:
	int plusfd[2];
	int subfd[2];
	int multfd[2];
	int divfd[2];
};

#endif
