#include "CalThreadPool.h"

CalThreadPool::CalThreadPool()
{
	fdCount = 0;

	if (pipe(plusfd) == -1) perror("create plus pipe error");
	if (pipe(subfd) == -1) perror("create sub pipe error");
	if (pipe(multfd) == -1) perror("create mult pipe error");
	if (pipe(divfd) == -1) perror("create div pipe error");
}

void CalThreadPool::SetPipefd(int fd)
{
	resultPipesfd[fdCount] = fd;
	fdCount ++;
}

void CalThreadPool::PlusThreadRun()
{
	pthread_t tid;
	int err;
	err = pthread_create(tid, NULL, PlusRequestHandler, NULL)
	if (err != 0)
		cout << strerror(err) << " : plus thread create error!"
			<< endl;
}

void PlusRequestHandler()
{
	while(1)
	{
		double x = 0;
		double y = 0;
		double result = 0;
		int n;
		if((n = read(plusfd[0], &x, sizeof(double))) == -1)
			perror("read plus pipe to x error");

		if ((n = read(plusfd[0], &y, sizeof(double))) == -1)
			perror("read plus pipe to y error");
		
		if (n == 0)
		{
			if (close(plusfd[0]) == -1)
				perror("close plue pipe error");
		}

		result = x + y;


	}
}


