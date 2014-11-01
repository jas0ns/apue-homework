#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

class Request{
public:
	Request(double x=0, double y=0)
		:x(x),y(y){}

	double x;
	double y;
};


int main(int argc, char **argv)
{
	//perror("fuck");
	int plusfd[2];
	int subfd[2];
	int multfd[2];
	int divfd[2];
	if (pipe(plusfd) == -1) perror("create plus pipe error");
	if (pipe(subfd) == -1) perror("create sub pipe error");
	if (pipe(multfd) == -1) perror("create mult pipe error");
	if (pipe(divfd) == -1) perror("create div pipe error");
	
	
	
	return 0;
}








