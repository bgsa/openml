#pragma once

#include "CppUnitTest.h"
#include <BinaryTree.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(BinaryTreeTest)
	{
	public:

		TEST_METHOD(BinaryTreeTest_nodeCount_Test)
		{
			BinaryTreeNode<std::string>* root = new BinaryTreeNode<std::string>("1");
			root->setLeftNode(new BinaryTreeNode<std::string>("2"));
			root->setRightNode(new BinaryTreeNode<std::string>("3"));

			root->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			root->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			root->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			root->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));

			root->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));

			BinaryTree<std::string>* tree = new BinaryTree<std::string>(root);

			int nodeCount = tree->nodeCount();

			Assert::AreEqual(8, nodeCount, L"wrong value", LINE_INFO());
		}

		TEST_METHOD(BinaryTreeTest_height_Test)
		{
			BinaryTreeNode<std::string>* root = new BinaryTreeNode<std::string>("1");
			root->setLeftNode(new BinaryTreeNode<std::string>("2"));
			root->setRightNode(new BinaryTreeNode<std::string>("3"));

			root->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			root->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			root->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			root->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));

			root->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));

			BinaryTree<std::string>* tree = new BinaryTree<std::string>(root);

			int height = tree->height();

			Assert::AreEqual(3, height, L"wrong value", LINE_INFO());
		}

		TEST_METHOD(BinaryTreeTest_levels_Test)
		{
			BinaryTreeNode<std::string>* root = new BinaryTreeNode<std::string>("1");
			root->setLeftNode(new BinaryTreeNode<std::string>("2"));
			root->setRightNode(new BinaryTreeNode<std::string>("3"));

			root->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			root->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			root->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			root->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));

			root->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));
			
			BinaryTree<std::string>* tree = new BinaryTree<std::string>(root);
			int levels = tree->levels();
			Assert::AreEqual(4, levels, L"wrong value", LINE_INFO());
			delete tree;

			tree = new BinaryTree<std::string>(nullptr);
			levels = tree->levels();
			Assert::AreEqual(0, levels, L"wrong value", LINE_INFO());
			delete tree;
		}

	};
}