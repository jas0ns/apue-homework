#ifndef REQUEST_H
#define REQUEST_H

class Request {

public:
	Request(){}

	Request(double x, double y, int fd)
		:x(x),y(y),resultPipeWfd(fd) {}

	double x;
	double y;
	int resultPipeWfd;
	long placeholder;
};

#endif
