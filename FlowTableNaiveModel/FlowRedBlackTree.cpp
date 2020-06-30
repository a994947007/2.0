#include "stdafx.h"
#include "FlowRedBlackTree.h"

FlowRedBlackTree::FlowRedBlackTree(Comparator<Flow*> * comparator,Equal<Flow*> * equal,SCBF * scbf) : RedBlackTree(comparator,equal),scbf(scbf)
{
}


ULONG FlowRedBlackTree::timeoutScan(Time & t)
{
	list<Flow*> list;
	return 0;
}

// 后序遍历删除节点可以减少调整开销
ULONG FlowRedBlackTree::timeoutScan(Time & tCur,Node<Flow*> * node) {
	ULONG len = 0;
	if (node != nullptr) {
		timeoutScan(tCur, node->left);
		timeoutScan(tCur, node->right);
		for (list<Flow*>::iterator itor = node->listElement.begin(); itor != node->listElement.end(); itor++,len++) {
			Time t = tCur - (*itor)->tLast;
			if (t.sec >= FLOW_TIMEOUT) {
				// 删除节点
				Flow * p = *itor;
				itor = node->listElement.erase(itor);
				delete p;
				// 如果节点中的元素数量小于1，直接删除
				if (node->listElement.size() == 0) {
					remove(node);
					break;
				}
			}
		}
	}
}