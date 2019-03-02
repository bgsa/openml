#include "BinaryTreeNode.h"

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode()
{
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(T value)
{
	this->value = value;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::leftNode()
{
	return lNode;
}

template <typename T>
void BinaryTreeNode<T>::setLeftNode(BinaryTreeNode<T>* leftNode) 
{
	if (this->lNode != nullptr)
		delete this->lNode;

	if (leftNode != nullptr)
		leftNode->pNode = this;

	this->lNode = leftNode;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::rightNode()
{
	return rNode;
}

template <typename T>
void BinaryTreeNode<T>::setRightNode(BinaryTreeNode<T>* rightNode)
{
	if (this->rNode != nullptr)
		delete this->rNode;

	if (rightNode != nullptr)
		rightNode->pNode = this;

	this->rNode = rightNode;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::parentNode()
{
	return pNode;
}

template <typename T>
bool BinaryTreeNode<T>::isRoot()
{
	return pNode == nullptr;
}

template <typename T>
bool BinaryTreeNode<T>::isLeaf()
{
	return lNode == nullptr && rNode == nullptr;
}

template <typename T>
bool BinaryTreeNode<T>::isInternalNode()
{
	return (!isLeaf()) && (!isRoot());
}

template <typename T>
int BinaryTreeNode<T>::height()
{
	int leftHeight = 0;
	int rightHeight = 0;

	if (lNode != nullptr)
		leftHeight = lNode->height() + 1;

	if (rNode != nullptr)
		rightHeight = rNode->height() + 1;

	return std::max(leftHeight, rightHeight);
}

template <typename T>
int BinaryTreeNode<T>::leftHeight()
{
	if (lNode == nullptr)
		return 0;

	return lNode->height() + 1;
}

template <typename T>
int BinaryTreeNode<T>::rightHeight()
{
	if (rNode == nullptr)
		return 0;

	return rNode->height() + 1;
}

template <typename T>
int BinaryTreeNode<T>::level()
{
	if (pNode == nullptr)
		return 1;

	return pNode->level() + 1;
}

template <typename T>
int BinaryTreeNode<T>::childrenCount()
{
	int count = 0;

	if (lNode != nullptr) 
	{
		count = lNode->childrenCount();
		count++;
	}

	if (rNode != nullptr) 
	{
		count += rNode->childrenCount();
		count++;
	}

	return count;
}
	
template <typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	if (lNode != nullptr)
	{
		delete lNode;
		lNode = nullptr;
	}

	if (rNode != nullptr)
	{
		delete rNode;
		rNode = nullptr;
	}
}

namespace OpenML
{
	template class BinaryTreeNode<std::string>;
	template class BinaryTreeNode<int>;
	template class BinaryTreeNode<float>;
	template class BinaryTreeNode<double>;
}