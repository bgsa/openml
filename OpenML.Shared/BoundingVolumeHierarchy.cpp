#include "BoundingVolumeHierarchy.h"

/*
void findClosestBoundingVolume(BinaryTreeNode<BoundingVolume>* node, const BoundingVolume& boundingVolume, BinaryTreeNode<BoundingVolume>* result)
{
	if (node == nullptr)
		result = nullptr;

	if (node->isLeaf())
		result = node;

	//Vec3<T> a = node->leftNode()->value.center();
}

void BoundingVolumeHierarchy::insert(const BoundingVolume& boundingVolume)
{
	if (isEmpty()) 
	{
		root = ALLOC_NEW(BinaryTreeNode<BoundingVolume>)(boundingVolume);
		return;
	}

	BinaryTreeNode<BoundingVolume> closestNode = closestBoundingVolume(boundingVolume);
}

BinaryTreeNode<BoundingVolume> BoundingVolumeHierarchy::closestBoundingVolume(const BoundingVolume& boundingVolume)
{
	BinaryTreeNode<BoundingVolume> node;

	findClosestBoundingVolume(root, boundingVolume, &node);

	return node;
}

*/