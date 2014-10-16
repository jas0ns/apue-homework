#ifndef TNODE_H
#define TNODE_H
#define N 10

typedef int DataType; 
class TNode {

public:
	TNode(DataType);
	TNode **GetChildren();
	DataType GetData();
	void SetChild(TNode *, int);

private:
	TNode *children[N];
	DataType data;
};

#endif
