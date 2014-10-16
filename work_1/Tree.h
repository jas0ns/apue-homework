#ifndef TREE_H
#define TREE_H
#include "TNode.h"

class Tree {

public:
	Tree();
	TNode *AddNode(DataType data, TNode *parent, int childIndex);
	bool RemoveNode(TNode *);
	TNode *GetRoot();
	void SetRoot(TNode *root);

private:
	TNode *root;
	int nodeCount;
};

#endif
