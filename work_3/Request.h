#ifndef REQUEST_H
#define REQUEST_H

class Request {

public:
	Request(){}

	Request(double x, double y, int qi):x(x),y(y),qi(qi) {}

	double x;
	double y;
	int qi;
};

#endif
