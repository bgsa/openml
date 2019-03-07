#include "BinaryTree.h"

template <class NodeType>
BinaryTree<NodeType>::BinaryTree()
{
	root = nullptr;
}

template <class NodeType>
BinaryTree<NodeType>::BinaryTree(BinaryTreeNode<NodeType>* root) 
{
	this->root = root;
}

template <class NodeType>
bool BinaryTree<NodeType>::isEmpty()
{
	return root == nullptr;
}

template <class NodeType>
int BinaryTree<NodeType>::nodeCount()
{
	if (isEmpty())
		return 0;

	return root->childrenCount() + 1;
}

template <class NodeType>
int BinaryTree<NodeType>::height()
{
	if (isEmpty())
		return 0;

	return root->height();
}

template <class NodeType>
int BinaryTree<NodeType>::levels()
{
	if (isEmpty())
		return 0;

	return root->height() + 1;
}

template <class NodeType>
std::vector<NodeType> BinaryTree<NodeType>::listPreOrder()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->listPreOrder();
}

template <class NodeType>
std::vector<NodeType> BinaryTree<NodeType>::listPostOrder()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->listPostOrder();
}

template <class NodeType>
std::vector<NodeType> BinaryTree<NodeType>::listInOrder()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->listInOrder();
}

template <class NodeType>
std::vector<NodeType> BinaryTree<NodeType>::leafs()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->leafs();
}

template <class NodeType>
std::vector<NodeType> BinaryTree<NodeType>::listLevelOrder()
{
	if (isEmpty())
		return std::vector<NodeType>();

	return root->listLevelOrder();
}

template <class NodeType>
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
	template class BinaryTree<BoundingVolume>;
}