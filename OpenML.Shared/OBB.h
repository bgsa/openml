#ifndef OBB_HEADER
#define OBB_HEADER

#include "Vec3.h"
#include "BoundingVolume.h"

namespace OpenML
{
	class OBB
		: public BoundingVolumeOBB
	{
	public:
		Vec3f center;
		Vec3f halfWidth;
		Mat3f orientation;

		/// <summary>
		/// Build a new unit OBB with width, height and depth 1.0 and orientation aligned to axis located on coordinates (0,0,0) 
		/// </summary>
		OBB(const Vec3f& center = Vec3f(0.0f));

		/// <summary>
		/// Translate the OBB
		/// </summary>
		API_INTERFACE OBB* translate(float xAxis, float yAxis, float zAxis) override;

		/// <summary>
		/// Rotate the OBB
		/// </summary>
		API_INTERFACE OBB* rotate(float angleInRadians, float xAxis, float yAxis, float zAxis) override;

		/// <summary>
		/// Scale the OBB
		/// </summary>
		API_INTERFACE OBB* scale(float xAxis, float yAxis, float zAxis) override;

		/// <summary>
		/// Get the model view matrix of OBB
		/// </summary>
		API_INTERFACE Mat3f modelView() override;

		///<summary>
		/// Check whether the OBBs are in contact each other
		///</summary>
		API_INTERFACE CollisionStatus collisionStatus(const OBB& aabb);

		// TODO: verificar colisao com AABB

		// TODO: verificar colisao com esferas
		
	};
}

#endif OBB_HEADER
