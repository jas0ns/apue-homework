#include "Tree.h"

Tree::Tree():nodeCount(0),root(0){}

TNode *Tree::AddNode(DataType data, TNode *parent, int childIndex)
{	
	TNode *tNode = new TNode(data);

	if (!parent)
	{
		this -> root = tNode;
	}
	else
	{
		parent -> SetChild(tNode, childIndex);
	}

	this -> nodeCount ++;
	return tNode;
}

TNode *Tree::GetRoot()
{
	return this -> root;
}


void Tree::SetRoot(TNode *root)
{
	this -> root = root;
}

bool Tree::RemoveNode(TNode *tnode)
{
	return true;
}


