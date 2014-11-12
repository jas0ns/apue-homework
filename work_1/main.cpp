#include "Tree.h"
#include <queue>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define random(x) (1+(rand()%(x)))

using namespace std;

void printTree(Tree tree);
void saveTree(Tree tree);
Tree readTree();
Tree generateRandomTree();
void err(const char *errMsg)
{
	cout << errMsg << endl;
	exit(1);
}

int main(int argc, char **agrv)
{
	//Tree tree = generateRandomTree();
	//printTree(tree);
	//saveTree(tree);
	//readTree();
	printTree(readTree());
	return 0;
}

void printTree(Tree tree)
{
	TNode *root = tree.GetRoot();

	queue<TNode *> tnq;

	tnq.push(tree.GetRoot());
	int count = 1;
	while (!tnq.empty())
	{
		TNode *parent = tnq.front();
		cout << parent->GetData() << " ";
		for (int i=0; i<10; i++)
		{
			if (parent->GetChildren()[i] != NULL)
			{
				tnq.push(parent->GetChildren()[i]);
				count ++;
			}
		}
		tnq.pop();
	}
}

void saveTree(Tree tree)
{
	const char *path = "./tree.file";
	int fd;

	if ((fd = open(path, O_WRONLY|O_APPEND|O_TRUNC|O_CREAT)) < 0)
		err("open writeonly file error!");

	TNode *root = tree.GetRoot();

	queue<TNode *> tnq;

	tnq.push(tree.GetRoot());
	int count = 1;
	while (!tnq.empty())
	{
		TNode *parent = tnq.front();
		DataType data = parent -> GetData();
		if (write(fd, &data, sizeof(DataType)) < sizeof(DataType))
			err("write file error!");

		for (int i=0; i<10; i++)
		{
			if (parent->GetChildren()[i] != NULL)
			{
				tnq.push(parent->GetChildren()[i]);
			}
			else
			{
				if (count <= 111111)
					tnq.push(new TNode(0));
			}
		}
		tnq.pop();
		count ++;
	}

	if (close(fd) < 0 )
		err("close file error!");
}

Tree readTree()
{
	Tree tree;
	queue<TNode *> tnq;
	const char *path = "./tree.file";
	int fd;
	if ((fd=open(path, O_RDONLY)) < 0)
		err("open readonly file error!");
	
	DataType data = 0;
	if (read(fd, &data, sizeof(DataType)) < sizeof(DataType))
		err("read root node error!");
	TNode *root = new TNode(data); 
	
	tree.SetRoot(root);
	tnq.push(tree.GetRoot());
	
	int nodecount = 1;
	ssize_t flag = 1;
	while (!tnq.empty())
	{
		if (flag == 0) break;
		TNode *parent = tnq.front();
		for (int i=0; i<10; i++)
		{
			flag = read(fd, &data, sizeof(DataType));
			if (data == 0) continue; //this child node is null
			if (flag == 0) break;
			if (flag < 0)
				err("read node error!");

			tnq.push(tree.AddNode(data, parent, i));
			nodecount ++;
		}
		tnq.pop();
	}

//	cout << "read node count is : " << nodecount << endl;
	if (close(fd) < 0 )
		err("close file error!");

	return tree;
}

Tree generateRandomTree()
{	
	srand(unsigned(time(0)));

	Tree tree;
	queue<TNode *> tnq;

	TNode *root = new TNode(random(1111111));
	//TNode *root = new TNode(1);
	tree.SetRoot(root);
	tnq.push(tree.GetRoot());
	long count = 1;
	long nodecount = 1;
	DataType data = 0;
	while (!tnq.empty())
	{
		if (count >= 1111111) break;
		TNode *parent = tnq.front();
		for (int i=0; i<10; i++)
		{
			if (! (count > 121111 && count < 221111 || count == 444444))
			{
				data = random(1111111);
				//data = i+1;
				tnq.push(tree.AddNode(data, parent, i));
				nodecount ++;
				count ++;
			}
			else 
			{
				count ++;
				continue;
			}
		}
		tnq.pop();
	}
//	cout << "save node count is : " << nodecount << endl; 
	return tree;
}
