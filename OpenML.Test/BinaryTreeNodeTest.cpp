#pragma once

#include "CppUnitTest.h"
#include <BinaryTreeNode.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(BinaryTreeNodeTest)
	{
	public:

		TEST_METHOD(BinaryTreeNodeTest_childrenCount_Test)
		{
			BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>("1");
			node->setLeftNode(new BinaryTreeNode<std::string>("2"));
			node->setRightNode(new BinaryTreeNode<std::string>("3"));

			node->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			node->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			node->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			node->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));
			
			node->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));

			int childrenCount = node->childrenCount();

			Assert::AreEqual(7, childrenCount, L"wrong value", LINE_INFO());
		}

		TEST_METHOD(BinaryTreeNodeTest_height_Test)
		{
			BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>("1");
			node->setLeftNode(new BinaryTreeNode<std::string>("2"));
			node->setRightNode(new BinaryTreeNode<std::string>("3"));

			node->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			node->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			node->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			node->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));

			node->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));

			int height = node->height();

			Assert::AreEqual(3, height, L"wrong value", LINE_INFO());
		}

		TEST_METHOD(BinaryTreeNodeTest_leftHeight_Test)
		{
			BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>("1");
			node->setLeftNode(new BinaryTreeNode<std::string>("2"));
			node->setRightNode(new BinaryTreeNode<std::string>("3"));

			node->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			node->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			node->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			node->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));

			node->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));

			int height = node->leftHeight();

			Assert::AreEqual(3, height, L"wrong value", LINE_INFO());
		}

		TEST_METHOD(BinaryTreeNodeTest_rightHeight_Test)
		{
			BinaryTreeNode<std::string>* node = new BinaryTreeNode<std::string>("1");
			node->setLeftNode(new BinaryTreeNode<std::string>("2"));
			node->setRightNode(new BinaryTreeNode<std::string>("3"));

			node->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			node->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			node->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			node->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));

			node->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));

			int height = node->rightHeight();

			Assert::AreEqual(2, height, L"wrong value", LINE_INFO());
		}

		TEST_METHOD(BinaryTreeNodeTest_level_Test)
		{
			BinaryTreeNode<std::string>* root = new BinaryTreeNode<std::string>("1");
			root->setLeftNode(new BinaryTreeNode<std::string>("2"));
			root->setRightNode(new BinaryTreeNode<std::string>("3"));

			root->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("4"));
			root->leftNode()->setRightNode(new BinaryTreeNode<std::string>("5"));

			root->leftNode()->leftNode()->setLeftNode(new BinaryTreeNode<std::string>("6"));
			root->leftNode()->leftNode()->setRightNode(new BinaryTreeNode<std::string>("7"));

			root->rightNode()->setRightNode(new BinaryTreeNode<std::string>("8"));

			int level = root->level();
			Assert::AreEqual(1, level, L"wrong value", LINE_INFO());

			level = root->rightNode()->level();
			Assert::AreEqual(2, level, L"wrong value", LINE_INFO());

			level = root->rightNode()->rightNode()->level();
			Assert::AreEqual(3, level, L"wrong value", LINE_INFO());

			level = root->leftNode()->leftNode()->leftNode()->level();
			Assert::AreEqual(4, level, L"wrong value", LINE_INFO());
		}
		
	};
}