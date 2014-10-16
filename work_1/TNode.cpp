#include "TNode.h"
#include <stdlib.h>

TNode::TNode(DataType data):data(data)
{
	for (int i=0; i<N; i++)
	{
		this -> children[i] = NULL;
	}
}

TNode **TNode::GetChildren()
{
	return this -> children;
}

DataType TNode::GetData()
{
	return this -> data;
}

void TNode::SetChild(TNode *tNode, int childIndex)
{
	this -> children[childIndex] = tNode;
}
