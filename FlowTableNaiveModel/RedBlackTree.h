#pragma once
#include "BBSTree.h"

static const bool RED = false;
static const bool BLACK = true;

template <typename E>
class RBNode :public Node<E> {
public:
	bool color;
public:
	RBNode(E e, Node<E>* parent) :Node<E>(e, parent) {
		color = RED;
	}
};

//红黑树
template <typename E>
class RedBlackTree :public BBSTree<E>
{
public:
	RedBlackTree(Comparator<E>* comparator, Equal<E>* equal) :BBSTree<E>(comparator, equal) {

	}
	RedBlackTree() : RedBlackTree<E>(nullptr, nullptr) {

	}
private:
	Node<E>* color(Node<E>* node, bool color) {
		if (node == nullptr) {
			return node;
		}
		((RBNode<E>*)node)->color = color;
		return node;
	}

	Node<E>* red(Node<E>* node) {
		return color(node, RED);
	}

	Node<E>* black(Node<E>* node) {
		return color(node, BLACK);
	}

	bool colorOf(Node<E>* node) {
		return node == nullptr ? BLACK : ((RBNode<E>*)node)->color;	//空节点默认为black
	}

	bool isBlack(Node<E>* node) {
		return colorOf(node) == BLACK;
	}

	bool isRed(Node<E>* node) {
		return colorOf(node) == RED;
	}

protected:
	virtual Node<E>* createNode(E e, Node<E>* parent) {
		return new RBNode<E>(e, parent);
	}
	virtual void afterAdd(Node<E>* node) {
		Node<E>* parent = node->parent;
		//添加的根结点
		if (parent == nullptr) {
			black(node);
			return;
		}
		if (isBlack(parent))	return;

		Node<E>* uncle = parent->sibling();
		Node<E>* grand = parent->parent;

		//叔父结点是红色，B树上溢
		if (isRed(uncle)) {
			black(uncle);
			black(parent);
			red(grand);
			afterAdd(grand);
			return;
		}

		//叔父结点为黑色，（可以理解为当前节点的sibling == null）
		if (parent->isLeftChild()) {
			if (node->isLeftChild()) {
				black(parent);
				red(grand);
				this->rotateRight(grand);
			}
			else {
				black(node);
				red(parent);
				red(grand);
				this->rotateLeft(parent);
				this->rotateRight(grand);
			}
		}
		else {
			if (node->isLeftChild()) {
				black(node);
				red(parent);
				red(grand);
				this->rotateRight(parent);
				this->rotateLeft(grand);
			}
			else {
				black(parent);
				red(grand);
				this->rotateLeft(grand);
			}
		}
	}
	virtual void afterRemove(Node<E>* node, Node<E>* replacement) {
		if (isRed(node)) {
			BSTree<E>::afterRemove(node, replacement);
			return;
		}
		if (isRed(replacement)) {
			black(replacement);
			BSTree<E>::afterRemove(node, replacement);
			return;
		}
		Node<E>* parent = node->parent;
		if (parent == nullptr) {
			BSTree<E>::afterRemove(node, replacement);
			return;
		}

		//来到这，删除的一定是黑色叶子结点，parent.left == nullptr的原因是被删后，parent的left属性==nullptr
		//或者由于递归操作，B树下溢，node是isLeftChild
		bool left = parent->left == nullptr || node->isLeftChild();
		//parent.left属性被清空，无法直接使用sbling()获取兄弟节点
		Node<E>* sibling = left ? parent->right : parent->left;
		if (left) {
			if (isRed(sibling)) {
				black(sibling);
				red(parent);
				this->rotateLeft(parent);
				sibling = parent->right;
			}
			if (isBlack(sibling->left) && isBlack(sibling->right)) {
				bool parentBlack = isBlack(parent);
				red(sibling);
				black(parent);
				if (parentBlack) {
					afterRemove(parent, nullptr);
				}
			}
			else {
				if (isBlack(sibling->right)) {
					this->rotateRight(sibling);
					sibling = parent->right;
				}
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->right);
				this->rotateLeft(parent);
			}
		}
		else {
			if (isRed(sibling)) {
				red(parent);
				black(sibling);
				this->rotateRight(parent);
				sibling = parent->left;
			}
			if (isBlack(sibling->left) && isBlack(sibling->right)) {
				bool parentBlack = isBlack(parent);
				black(parent);
				red(sibling);
				if (parentBlack) {
					afterRemove(parent, nullptr);
				}
			}
			else {
				if (isBlack(sibling->left)) {
					this->rotateLeft(sibling);
					sibling = parent->left;
				}
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->left);
				this->rotateRight(parent);
			}
		}
		BSTree<E>::afterRemove(node, replacement);
	}
};

