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

		TEST_METHOD(BinaryTreeTest_listPreOrder_Test)
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
			std::vector<std::string> list = tree->listPreOrder();

			std::string expected[8] = {
				"1", "2", "4", "6", "7", "5" , "3" , "8"
			};

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(list[i], expected[i], L"wrong value", LINE_INFO());

			delete tree;
		}

		TEST_METHOD(BinaryTreeTest_listPostOrder_Test)
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
			std::vector<std::string> list = tree->listPostOrder();

			std::string expected[8] = {
				"6", "7", "4", "5", "2", "8" , "3" , "1"
			};

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(list[i], expected[i], L"wrong value", LINE_INFO());

			delete tree;
		}

		TEST_METHOD(BinaryTreeTest_listInOrder_Test)
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
			std::vector<std::string> list = tree->listInOrder();

			std::string expected[8] = {
				"6", "4", "7", "2", "5", "1" , "3" , "8"
			};

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(list[i], expected[i], L"wrong value", LINE_INFO());

			delete tree;
		}

		TEST_METHOD(BinaryTreeTest_listLevelOrder_Test)
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
			std::vector<std::string> list = tree->listLevelOrder();

			std::string expected[8] = {
				"1", "2", "3", "4", "5", "8" , "6" , "7"
			};

			for (size_t i = 0; i < 8; i++)
				Assert::AreEqual(list[i], expected[i], L"wrong value", LINE_INFO());

			delete tree;
		}

	};
}