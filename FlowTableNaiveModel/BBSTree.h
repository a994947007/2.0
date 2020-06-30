#pragma once
#include "BSTree.h"


template <typename E>
class BBSTree :public BSTree<E>
{
public:
	BBSTree(Comparator<E>* comparator, Equal<E>* equal) :BSTree<E>(comparator, equal) {
	}

	BBSTree() :BBSTree<E>(nullptr, nullptr) {
	}
protected:
	virtual void rotateLeft(Node<E>* grand) {
		Node<E>* parent = grand->right;
		Node<E>* child = parent->left;
		grand->right = child;
		parent->left = grand;
		parent->parent = grand->parent;
		if (grand->isLeftChild()) {
			grand->parent->left = parent;
		}
		else if (grand->isRightChild()) {
			grand->parent->right = parent;
		}
		else {
			this->root = parent;
		}
		if (child != nullptr) {
			child->parent = grand;
		}
		grand->parent = parent;
	}

	virtual void rotateRight(Node<E>* grand) {
		Node<E>* parent = grand->left;
		Node<E>* child = parent->right;
		grand->left = child;
		parent->right = grand;
		parent->parent = grand->parent;
		if (grand->isLeftChild()) {
			grand->parent->left = parent;
		}
		else if (grand->isRightChild()) {
			grand->parent->right = parent;
		}
		else {
			this->root = parent;
		}
		if (child != nullptr) {
			child->parent = grand;
		}
		grand->parent = parent;
	}
};

