#pragma once

#include "OpenML.h"
#include <algorithm>
#include <vector>

namespace OpenML
{

	template <typename T>
	class BinaryTreeNode
	{
	private:
		BinaryTreeNode<T>* pNode = nullptr;
		BinaryTreeNode<T>* lNode = nullptr;
		BinaryTreeNode<T>* rNode = nullptr;

	public:
		T value;

		API_INTERFACE BinaryTreeNode();
		API_INTERFACE BinaryTreeNode(T value);

		API_INTERFACE BinaryTreeNode<T>* leftNode();
		API_INTERFACE void setLeftNode(BinaryTreeNode<T>* leftNode);

		API_INTERFACE BinaryTreeNode<T>* rightNode();
		API_INTERFACE void setRightNode(BinaryTreeNode<T>* rightNode);

		API_INTERFACE BinaryTreeNode<T>* parentNode();
		
		API_INTERFACE bool isRoot();
		API_INTERFACE bool isLeaf();
		API_INTERFACE bool isInternalNode();

		API_INTERFACE int height();
		API_INTERFACE int leftHeight();
		API_INTERFACE int rightHeight();
		API_INTERFACE int level();
		API_INTERFACE int childrenCount();

		API_INTERFACE std::vector<T> listPreOrder();
		API_INTERFACE std::vector<T> listPostOrder();	
		API_INTERFACE std::vector<T> listInOrder();

		~BinaryTreeNode();
	};

}