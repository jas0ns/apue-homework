#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "CalThreadPool.h"

using namespace std;

int main(int argc, char **argv)
{
	CalThreadPool calThreadPool;

	int plusWfd = calThreadPool.GetPlusPipeWfd();
	int resultPipefd[2];
	
	if (pipe(resultPipefd) == -1)
		perror("create result pipe error");
	
	pid_t pid;
	if((pid = fork()) == -1)
		perror("create request process error")
	if (pid == 0)
	{
		for(int i=0; i<100; i++)
		{
			Request request(i, 100, resultPipefd[1]);
			if(write(plusWfd, &request, sizeof(Request)) == -1)
				perror("write plus request to pipe error");
		}
	}
	else
	{
		calThreadPool.PlusThreadRun();	
	}
	return 0;
}








