LANG=c

all : main.cpp 
	g++ -g -c main.cpp CalThreadPool.cpp
	g++ -g -lpthread -o main.out main.o CalThreadPool.o

clean : 
	rm -rf *.out *.o
