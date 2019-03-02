#include "BinaryTree.h"

template <typename NodeType>
BinaryTree<NodeType>::BinaryTree()
{
	root = nullptr;
}

template <typename NodeType>
BinaryTree<NodeType>::BinaryTree(BinaryTreeNode<NodeType>* root) 
{
	this->root = root;
}

template <typename NodeType>
bool BinaryTree<NodeType>::isEmpty()
{
	return root == nullptr;
}

template <typename NodeType>
int BinaryTree<NodeType>::nodeCount()
{
	if (isEmpty())
		return 0;

	return root->childrenCount() + 1;
}

template <typename NodeType>
int BinaryTree<NodeType>::height()
{
	if (isEmpty())
		return 0;

	return root->height();
}

template <typename NodeType>
int BinaryTree<NodeType>::levels()
{
	if (isEmpty())
		return 0;

	return root->height() + 1;
}

template <typename NodeType>
std::vector<NodeType> BinaryTree<NodeType>::listPreOrder()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->listPreOrder();
}

template <typename NodeType>
std::vector<NodeType> BinaryTree<NodeType>::listPostOrder()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->listPostOrder();
}

template <typename NodeType>
std::vector<NodeType> BinaryTree<NodeType>::listInOrder()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->listInOrder();
}

template <typename NodeType>
BinaryTree<NodeType>::~BinaryTree()
{
	if (root != nullptr)
	{
		delete root;
		root = nullptr;
	}
}

namespace OpenML
{
	template class BinaryTree<std::string>;
	template class BinaryTree<int>;
	template class BinaryTree<float>;
	template class BinaryTree<double>;
}