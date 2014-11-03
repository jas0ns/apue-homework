#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "CalThreadPool.h"

using namespace std;

int main(int argc, char **argv)
{
	CalThreadPool calThreadPool;//include create request pipe

	int plusWfd = calThreadPool.GetPlusPipeWfd();
	int resultPipefd[2];
	
	//create result pipe	
	if (pipe(resultPipefd) == -1)
		perror("create result pipe error");
	
	pid_t pid;
	if ((pid = fork()) == -1)
		perror("create request process error");
	if (pid == 0)
	{
		if (close(resultPipefd[0]) == -1)
			perror("close result pipe read port error");
		calThreadPool.ClosePipeWPort();
		calThreadPool.PlusThreadRun();	
	}
	else
	{
		if (close(resultPipefd[1]) == -1)
			perror("close result pipe write port error");
		calThreadPool.ClosePipeRPort();

		for(int i=0; i<100; i++)
		{
			Request request(i, 100, resultPipefd[1]);
			if (write(plusWfd, &request, sizeof(Request)) == -1)
				perror("write plus request to pipe error");
			
			int n;
			double result;
			if ((n=read(resultPipefd[0], &result, sizeof(double))) == -1)
				perror("read result pipe error");
			else if (n == 0)
			{
				if (close(resultPipefd[0]) == -1)
					perror("close result pipe read port error");
				break;
			}
			else
				cout << "receive result : " << result << endl;
		}
	}
	return 0;
}






