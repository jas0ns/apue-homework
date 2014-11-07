#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "CalThreadPool.h"

#define PLUSTHREADNUMBER 5
#define SUBTHREADNUMBER 3
#define MULTTHREADNUMBER 2
#define DIVTHREADNUMBER 2

using namespace std;

void *PullPlusRequest(void *arg);
void *PullSubRequest(void *arg);
void *PullMultRequest(void *arg);
void *PullDivRequest(void *arg);

int main(int argc, char **argv)
{
	CalThreadPool calThreadPool;// include create request pipe
	pid_t pid;
	if ((pid = fork()) == -1)
		perror("create request process error");
	if (pid == 0) // calculator process
	{
		pthread_t plustid = calThreadPool.PlusThreadRun(); // plus service thread
		pthread_t subtid = calThreadPool.SubThreadRun(); // sub service thread
		pthread_t multtid = calThreadPool.MultThreadRun(); // mult service thread
		pthread_t divtid = calThreadPool.DivThreadRun(); // div service thread

		pthread_join(plustid, NULL);
		pthread_join(subtid, NULL); 
		pthread_join(multtid, NULL); 
		pthread_join(divtid, NULL);      
	}
	else // request process
	{
		pthread_t plusReqtids[PLUSTHREADNUMBER];
		pthread_t subReqtids[SUBTHREADNUMBER];
		pthread_t multReqtids[MULTTHREADNUMBER];
		pthread_t divReqtids[DIVTHREADNUMBER];

		for (int i=0; i<PLUSTHREADNUMBER; i++)
		{
			int args[3] = {plusWfd, plusResultpfds[i][0], plusResultpfds[i][1]};
			int err;
			err = pthread_create(&(plusReqtids[i]), NULL, PullPlusRequest, args);
			if (err != 0)
				cout << strerror(err) 
					<< " : plus request thread create error" << endl;
		}

		for (int i=0; i<SUBTHREADNUMBER; i++)
		{
			int args[3] = {subWfd, subResultpfds[i][0], subResultpfds[i][1]};
			int err;
			err = pthread_create(&(subReqtids[i]), NULL, PullSubRequest, args);
			if (err != 0)
				cout << strerror(err) 
					<< " : sub request thread create error" << endl;
		}
		for (int i=0; i<MULTTHREADNUMBER; i++)
		{
			int args[3] = {multWfd, multResultpfds[i][0], multResultpfds[i][1]};
			int err;
			err = pthread_create(&(multReqtids[i]), NULL, PullMultRequest, args);
			if (err != 0)
				cout << strerror(err) 
					<< " : mult request thread create error" << endl;
		}
		for (int i=0; i<DIVTHREADNUMBER; i++)
		{
			int args[3] = {divWfd, divResultpfds[i][0], divResultpfds[i][1]};
			int err;
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
	}
	return 0;
}

void *PullPlusRequest(void *args)
{
	int _args[3] = {((int *)args)[0], ((int *)args)[1], ((int *)args)[2]};
	for(int i=0; i<10000; i++)
	{
		Request request(i, 100, _args[2]);
		if (write(_args[0], &request, sizeof(Request)) == -1)
			perror("write plus request to pipe error");
		
		int n;
		double result;
		if ((n=read(_args[1], &result, sizeof(double))) == -1)
			perror("read result pipe error");
		else if (n == 0)
		{
			if (close(_args[1]) == -1)
				perror("close result pipe read port error");
			break;
		}
		else
		{}
	}
}

void *PullSubRequest(void *args)
{
	int _args[3] = {((int *)args)[0], ((int *)args)[1], ((int *)args)[2]};
	for(int i=0; i<10000; i++)
	{
		Request request(i, 100, _args[2]);
		if (write(_args[0], &request, sizeof(Request)) == -1)
			perror("write plus request to pipe error");
		
		int n;
		double result;
		if ((n=read(_args[1], &result, sizeof(double))) == -1)
			perror("read result pipe error");
		else if (n == 0)
		{
			if (close(_args[1]) == -1)
				perror("close result pipe read port error");
			break;
		}
		else
		{}
	}
}

void *PullMultRequest(void *args)
{
	int _args[3] = {((int *)args)[0], ((int *)args)[1], ((int *)args)[2]};
	for(int i=0; i<10000; i++)
	{
		Request request(i, 100, _args[2]);
		if (write(_args[0], &request, sizeof(Request)) == -1)
			perror("write plus request to pipe error");
		
		int n;
		double result;
		if ((n=read(_args[1], &result, sizeof(double))) == -1)
			perror("read result pipe error");
		else if (n == 0)
		{
			if (close(_args[1]) == -1)
				perror("close result pipe read port error");
			break;
		}
		else
		{}
	}
}

void *PullDivRequest(void *args)
{
	int _args[3] = {((int *)args)[0], ((int *)args)[1], ((int *)args)[2]};
	for(int i=0; i<10000; i++)
	{
		Request request(i, 100, _args[2]);
		if (write(_args[0], &request, sizeof(Request)) == -1)
			perror("write div request to pipe error");
		
		int n;
		double result;
		if ((n=read(_args[1], &result, sizeof(double))) == -1)
			perror("read div result pipe error");
		else if (n == 0)
		{
			if (close(_args[1]) == -1)
				perror("close div result pipe read port error");
			break;
		}
		else
		{}
	}
}



