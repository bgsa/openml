#ifndef OBB_HEADER
#define OBB_HEADER

#include "Vec3.h"
#include "BoundingVolume.h"

namespace OpenML
{
	class OBB
		: public BoundingVolume
	{
	public:
		Vec3f center;
		Vec3f halfWidth;
		Mat3f orientation;

		/// <summary>
		/// Build a new unit OBB with width, height and depth 1.0 and orientation aligned to axis located on coordinates (0,0,0) 
		/// <summary>
		OBB(const Vec3f& center = Vec3f(0.0f), const Vec3f& halfWidth = Vec3f(0.5f));

		///<summary>
		/// Check whether the OBBs are in contact each other
		///</summary>
		API_INTERFACE ColisionStatus colisionStatus(const OBB& aabb);

		// TODO: verificar colisao com AABB

		// TODO: verificar colisao com esferas
		
	};
}

#endif OBB_HEADER
