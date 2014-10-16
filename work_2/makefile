LANG=c

all : main.cpp 
	g++ -g -c WordMap.cpp
	g++ -g -c WFreqCounter.cpp
	g++ -g -c generateMap.cpp
	g++ -g -c main.cpp
	g++ -g -o generateMap.out generateMap.o WFreqCounter.o WordMap.o
	g++ -g -o wordCount.out main.o WFreqCounter.o WordMap.o

clean : 
	rm -rf *.out *.o
