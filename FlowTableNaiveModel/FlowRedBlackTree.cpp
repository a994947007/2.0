#include "stdafx.h"
#include "FlowRedBlackTree.h"

FlowRedBlackTree::FlowRedBlackTree(Comparator<Flow*> * comparator,Equal<Flow*> * equal,SCBF * scbf) : BSTree(comparator,equal),scbf(scbf)
{
}


ULONG FlowRedBlackTree::timeoutScan(Time t)
{
	ULONG len = 0;
	timeoutScan(t, root,len);
	return len;
}

// 后序遍历删除节点可以减少调整开销
ULONG FlowRedBlackTree::timeoutScan(Time tCur,Node<Flow*> * node,ULONG & len) {
	if (node != nullptr) {
		list<Node<Flow *>*> stack1;
		list<Node<Flow *>*> stack2;
		stack1.push_back(node);
		while (stack1.size() != 0) {
			Node<Flow*> * p = stack1.back();
			stack1.pop_back();
			stack2.push_back(p);
			if (p->left != nullptr) {
				stack1.push_back(p->left);
			}
			if (p->right != nullptr) {
				stack1.push_back(p->right);
			}
		}
		while (stack2.size() != 0) {
			Node<Flow *> * s = stack2.back();
			stack2.pop_back();
			for (list<Flow*>::iterator itor = s->listElement.begin(); itor != s->listElement.end(); ) {
				Time t = tCur - (*itor)->tLast;
				if(t.sec > FLOW_TIMEOUT){
					Flow * tmp = (*itor);
					itor = s->listElement.erase(itor);
					scbf->filter_delete(*(SCFlow*)tmp);
					delete tmp;
					len++;
					if (s->listElement.size() == 0) {
						removeNode(s);
					}
				}
			}
		}
	}
	return len;
}