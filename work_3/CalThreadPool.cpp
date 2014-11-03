#include "CalThreadPool.h"

void *PlusRequestHandler(void *arg);

CalThreadPool::CalThreadPool()
{
	if (pipe(plusfd) == -1) perror("create plus pipe error");
	if (pipe(subfd) == -1) perror("create sub pipe error");
	if (pipe(multfd) == -1) perror("create mult pipe error");
	if (pipe(divfd) == -1) perror("create div pipe error");
}


void CalThreadPool::PlusThreadRun()
{
	pthread_t tid;
	int err;
	err = pthread_create(&tid, NULL, PlusRequestHandler, NULL);
	if (err != 0)
		cout << strerror(err) << " : plus thread create error!"
			<< endl;
}

int	CalThreadPool::GetPlusPipeWfd()
{
	return this->plusfd[1];
}

void *PlusRequestHandler(void *arg)
{
	int plusfd = *(int *)arg;
	while(1)
	{
		Request request;
		double result = 0;
		int n;
		if((n = read(plusfd, &request, sizeof(Request))) == -1)
			perror("read plus pipe to x error");
		else if (n == 0)
		{
			if (close(plusfd) == -1)
				perror("close plue pipe error");
			break;
		}

		result = request.x + request.y;

		if(write(request.resultPipeWfd, &result, sizeof(double)) == -1)
	 		perror("write result to pipe error");
	}
}



