#pragma once

#include <list>

using namespace std;

template <typename E>
class Node {
public:
	list<E> listElement;
	struct Node<E> * left;
	struct Node<E> * right;
	struct Node<E> * parent;
	Node(E e, Node<E> * parent) :parent(parent),left(nullptr),right(nullptr){
		listElement.push_back(e);
	}
	virtual bool isLeaf() {
		return left == nullptr && right == nullptr;
	}
	virtual bool hasTwoChildren() {
		if (left != nullptr && right != nullptr) {
			return true;
		}
		return false;
	}
	virtual bool isLeftChild() {
		return parent != nullptr && this == parent->left;
	}
	virtual bool isRightChild() {
		return parent != nullptr && this == parent->right;
	}
	virtual Node<E> * sibling() {
		if (parent == nullptr) return nullptr;
		if (isLeftChild()) {
			return parent->right;
		}
		else {
			return parent->left;
		}
	}
};

//¶þ²æÊ÷
template<typename E>
class BinaryTree
{
protected:
	int size;
	Node<E> * root;
public:
	BinaryTree() :root(nullptr), size(0) {}
	virtual int getSize() {
		return size;
	}
	virtual bool isEmpty() {
		return root == nullptr;
	}
	virtual void clear() {
		deleteTree(root);
		size = 0;
		root = nullptr;
	}
	virtual void deleteTree(Node<E>* node) {
		if (node != nullptr) {
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}
	virtual ~BinaryTree() {
		clear();
	}
protected:
	virtual Node<E>* createNode(E e, Node<E>* parent) {
		return new Node<E>(e, parent);
	}
};

