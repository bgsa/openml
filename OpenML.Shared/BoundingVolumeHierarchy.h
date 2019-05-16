#pragma once

#include "BoundingVolume.h"
#include "BinaryTree.h"

namespace OpenML
{

	class BoundingVolumeHierarchy
		: public BinaryTree<BoundingVolume<float>>
	{
	public:

		void insert(const BoundingVolume<float>& boundingVolume);
		BinaryTreeNode<BoundingVolume<float>> closestBoundingVolume(const BoundingVolume<float>& boundingVolume);

	};

}