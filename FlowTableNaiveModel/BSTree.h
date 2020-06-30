#pragma once
#include "BinaryTree.h"
#include "Comparator.h"
#include "Equal.h"

using namespace std;
//����������
template<typename E>
class BSTree :
	public BinaryTree<E>
{
private:
	Comparator <E> * comparator;
	Equal<E> * equal;
public:
	BSTree(Comparator<E>* comparator, Equal<E>* equal) :BinaryTree<E>(), comparator(comparator), equal(equal) {}
	BSTree() :BSTree<E>(nullptr, nullptr) {}

	virtual void add(E e) {
		if (e == nullptr) {
			return;
		}
		if (this->root == nullptr) {
			this->root = this->createNode(e, nullptr);
			this->size++;
			afterAdd(this->root);
			return;
		}
		Node<E>* parent = this->root;
		Node<E>* node = this->root;
		int cmp = 0;
		while (node != nullptr) {
			parent = node;
			//node�е�e�Ĵ�С����һ����
			cmp = comparator->compare(e, node->listElement.front());
			if (cmp < 0) {
				node = node->left;
			}
			else if (cmp > 0) {
				node = node->right;
			}
			else {
				//���Node���Ƿ���ڸ�Ԫ�أ�����ֱ�ӷ��أ��������
				for (typename list<E>::iterator itor = node->listElement.begin(); itor != node->listElement.end(); itor++) {
					if (equal->equals(*itor, e)) {
						return;
					}
				}
				node->listElement.push_back(e);
				this->size++;
				return;	
			}
		}
		Node<E>* newNode = this->createNode(e, parent);
		if (cmp > 0) {
			parent->right = newNode;
		}
		else {
			parent->left = newNode;
		}
		this->size++;
		afterAdd(newNode);
	}

	virtual void remove(E e) {
		if (e == nullptr) {
			return;
		}
		Node<E>* node = this->root;
		while (node != nullptr) {
			int cmp = compare(e, node->listElement.front());
			if (cmp == 0) {
				if (node->listElement.size() == 1) {
					this->size--;
					remove(node);
					return;
				}
				typename list<E>::iterator itor;
				for (itor = node->listElement.begin(); itor != node->listElement.end(); ) {
					if (equal->equals(*itor, e)) {	
						itor = node->listElement.erase(itor);
						this->size--;
						return;
					}
					else {
						itor++;
					}
				}
			}
			else if (cmp > 0) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
	}

	virtual bool contains(E e) {
		return node(e) == nullptr;
	}

	//���в���e�������ز��ҵĲ�������
	virtual ULONG find(E e,E & result) {
		int len = 0;
		if (this->root == nullptr) {
			return 0;
		}
		Node<E>* node = this->root;
		while (node != nullptr) {
			int cmp = comparator->compare(e, node->listElement.front());
			len++;
			if (cmp == 0) {
				for (typename list<E>::iterator itor = node->listElement.begin(); itor != node->listElement.end(); itor++) {
					len++;
					if (equal->equals(*itor, e)) {
						result = *itor;
						return len;
					}
				}
			}
			else if (cmp > 0) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
		return len;
	}

protected:
	virtual Node<E>* predessor(Node<E>* node) {
		if (node == nullptr) {
			return nullptr;
		}
		Node<E>* p = node->left;
		if (p != nullptr) {
			while (p->right != nullptr) {
				p = p->right;
			}
			return p;
		}
		while (node->parent != nullptr && node->parent->left == node) {
			node = node->parent;
		}
		return node->parent;
	}

	virtual Node<E>* successor(Node<E>* node) {
		if (node == nullptr) {
			return nullptr;
		}
		Node<E>* p = node->right;
		if (p != nullptr) {
			while (p->left != nullptr) {
				p = p->left;
			}
			return p;
		}
		while (node->parent != nullptr && node == node->parent->right) {
			node = node->parent;
		}
		return node->parent;
	}

	virtual void afterAdd(Node<E>* node) {}

	virtual void afterRemove(Node<E>* node, Node<E>* replacement) {
		if (node != nullptr) {
			delete node;
			node = nullptr;
		}
	}

private:
	int compare(E e1, E e2) {
		if (comparator != nullptr) {
			return comparator->compare(e1, e2);
		}
		else {
			return e1 - e2 > 0 ? 1 : (e1 - e2 < 0 ? -1 : 0);
		}
	}

	Node<E>* node(E e) {
		Node<E>* node = this->root;
		while (node != nullptr) {
			int cmp = comparator->compare(e, node->listElement.front());
			if (cmp == 0) {
				return node;
			}
			else if (cmp > 0) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}
		return nullptr;
	}
protected:
	//��㱻ɾ��ʱ�������ֻʣ1��Ԫ��
	void remove(Node<E>* node) {
		//��Ϊ2�Ľ��ֱ��Ѱַ����滻����
		if (node->hasTwoChildren()) {
			Node<E>* s = successor(node);
			for(typename list<E>::iterator itor = s->listElement.begin(); itor != s->listElement.end(); itor++){
				node->listElement.push_back(*itor);
			}
			node = s;
		}
		//ɾ����Ϊ1���߶�Ϊ0�Ľ��
		Node<E>* replacement = node->left != nullptr ? node->left : node->right;
		if (replacement != nullptr) {
			replacement->parent = node->parent;
			if (node->isLeftChild()) {
				node->parent->left = replacement;
			}
			else if (node->isRightChild()) {
				node->parent->right = replacement;
			}
			else if (node == this->root) {
				this->root = replacement;
				this->root->parent = nullptr;
			}
		}
		else {
			if (node->parent == nullptr) {
				this->root = nullptr;
			}
			else {
				if (node->isLeftChild()) {
					node->parent->left = nullptr;
				}
				else {
					node->parent->right = nullptr;
				}
			}
		}
		//�ͷű�ɾ�����Ȳ���
		afterRemove(node, replacement);
	}
};

