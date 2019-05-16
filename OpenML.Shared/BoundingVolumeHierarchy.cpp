#include "BoundingVolumeHierarchy.h"

void findClosestBoundingVolume(BinaryTreeNode<BoundingVolume<float>>* node, const BoundingVolume<float>& boundingVolume, BinaryTreeNode<BoundingVolume<float>>* result)
{
	if (node == nullptr)
		result = nullptr;

	if (node->isLeaf())
		result = node;

	//Vec3<T> a = node->leftNode()->value.center();
}

void BoundingVolumeHierarchy::insert(const BoundingVolume<float>& boundingVolume)
{
	if (isEmpty()) 
	{
		root = new BinaryTreeNode<BoundingVolume<float>>(boundingVolume);
		return;
	}

	BinaryTreeNode<BoundingVolume<float>> closestNode = closestBoundingVolume(boundingVolume);
}

BinaryTreeNode<BoundingVolume<float>> BoundingVolumeHierarchy::closestBoundingVolume(const BoundingVolume<float>& boundingVolume)
{
	BinaryTreeNode<BoundingVolume<float>> node;

	findClosestBoundingVolume(root, boundingVolume, &node);

	return node;
}

