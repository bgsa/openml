#pragma once

#include "OpenML.h"
#include "BinaryTreeNode.h"

namespace OpenML
{

	template <typename NodeType>
	class BinaryTree
	{
	public:
		BinaryTreeNode<NodeType>* root;

		API_INTERFACE BinaryTree();
		API_INTERFACE BinaryTree(BinaryTreeNode<NodeType>* root);

		API_INTERFACE bool isEmpty();
		API_INTERFACE int nodeCount();
		API_INTERFACE int height();
		API_INTERFACE int levels();

		~BinaryTree();
	};

}