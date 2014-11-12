make : all

TNode.o : TNode.cpp TNode.h
	g++ -c TNode.cpp
Tree.o : Tree.cpp Tree.h
	g++ -c Tree.cpp
main.o : main.cpp
	g++ -c main.cpp
main : TNode.o Tree.o main.o
	g++ -o main.out main.o TNode.o Tree.o
all : TNode.cpp TNode.h Tree.cpp Tree.h main.cpp
	g++ -c -g TNode.cpp
	g++ -c -g Tree.cpp
	g++ -c -g main.cpp
	g++ -g -o main.out TNode.o Tree.o main.o
clean : 
	rm -rf *.out *.o

