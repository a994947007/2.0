#pragma once
#include "uniform.h"
#include "RedBlackTree.h"
#include "SCBF.h"

class FlowRedBlackTree :public RedBlackTree<Flow *>
{
private:
	SCBF * scbf;

public:
	FlowRedBlackTree(Comparator<Flow*> *, Equal<Flow*> * ,SCBF *);
	ULONG timeoutScan(Time &);

private:
	ULONG timeoutScan(Time &, Node<Flow*> *);
};

