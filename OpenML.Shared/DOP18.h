#ifndef DOP18_HEADER
#define DOP18_HEADER

#include "Vec3.h"
#include "BoundingVolume.h"
#include "Plane3D.h"

#define DOP18_ORIENTATIONS 9

namespace OpenML
{
	/// <summary>
	/// Represents a k-DOP with 9 orientations and 18 DOPs
	/// Normal coordinates od planes:
	///
	///     axis-aligned:
	///		{ -1,  0,  0 } - left
	///		{  1,  0,  0 } - right
	///		{  0,  1,  0 } - up
	///		{  0, -1,  0 } - down
	///		{  0,  0, -1 } - front
	///		{  0,  0,  1 } - depth
	///
	///     edges cut-off:
	///		{ -1,  1,  0 } - up-left
	///		{  1, -1,  0 } - down-right
	///		{  1,  1,  0 } - up-right
	///		{ -1, -1,  0 } - down-left
	///		{  0,  1, -1 } - up-front
	///		{  0, -1,  1 } - down-depth
	///		{  0,  1,  1 } - up-depth
	///		{  0, -1, -1 } - down-front
	///		{ -1,  0,  1 } - left-depth
	///		{  1,  0, -1 } - right-front
	///		{  1,  0,  1 } - right-depth
	///		{ -1,  0, -1 } - left-front
	///
	/// </summary>
	class DOP18
		: public BoundingVolumeDOP18
	{
	public:
		float min[DOP18_ORIENTATIONS];
		float max[DOP18_ORIENTATIONS];

		/// <summary>
		/// Default constructur - build a unit k-DOP with the center in the origin
		/// </summary>
		API_INTERFACE inline DOP18();

		/// <summary>
		/// Get the normals of k-DOP planes
		/// </summary>
		API_INTERFACE inline const Vec3f* normals()
		{
			const static Vec3f normal[18] = {
				{ -1.0f,  0.0f,  0.0f },
				{  1.0f,  0.0f,  0.0f },
				{  0.0f,  1.0f,  0.0f },
				{  0.0f, -1.0f,  0.0f },
				{  0.0f,  0.0f, -1.0f },
				{  0.0f,  0.0f,  1.0f },

				{ -0.5f,  0.5f,  0.0f },
				{  0.5f, -0.5f,  0.0f },
				{  0.5f,  0.5f,  0.0f },
				{ -0.5f, -0.5f,  0.0f },
				{  0.0f,  0.5f, -0.5f },
				{  0.0f, -0.5f,  0.5f },
				{  0.0f,  0.5f,  0.5f },
				{  0.0f, -0.5f, -0.5f },
				{ -0.5f,  0.0f,  0.5f },
				{  0.5f,  0.0f, -0.5f },
				{  0.5f,  0.0f,  0.5f },
				{ -0.5f,  0.0f, -0.5f }
			};

			return &normal[0];
		}

		/// <summary>
		/// Get the k-DOP planes
		/// </summary>
		API_INTERFACE inline Plane3D* planes()
		{
			const Vec3f* n = normals();

			Plane3D* result = ALLOC_NEW_ARRAY(Plane3D, 18) {
				Plane3D(Vec3f(min[0], 0.0f, 0.0f), n[0]), // left
					Plane3D(Vec3f(max[0], 0.0f, 0.0f), n[1]), // right

					Plane3D(Vec3f(0.0f, max[1], 0.0f), n[2]), // up
					Plane3D(Vec3f(0.0f, min[1], 0.0f), n[3]), // down

					Plane3D(Vec3f(0.0f, 0.0f, min[2]), n[4]), // front
					Plane3D(Vec3f(0.0f, 0.0f, max[2]), n[5]), // depth

					Plane3D(Vec3f(min[3], max[3], 0.0f), n[6]), // up-left
					Plane3D(Vec3f(max[3], min[3], 0.0f), n[7]), // down-right

					Plane3D(Vec3f(max[4], max[4], 0.0f), n[8]), // up-right
					Plane3D(Vec3f(min[4], min[4], 0.0f), n[9]), // down-left

					Plane3D(Vec3f(0.0f, max[5], min[5]), n[10]), // up-front
					Plane3D(Vec3f(0.0f, min[5], max[5]), n[11]), // down-depth

					Plane3D(Vec3f(0.0f, max[6], max[6]), n[12]), // up-depth
					Plane3D(Vec3f(0.0f, min[6], min[6]), n[13]), // down-front

					Plane3D(Vec3f(min[7], 0.0f, max[7]), n[14]), // left-depth
					Plane3D(Vec3f(max[7], 0.0f, min[7]), n[15]), // right-front

					Plane3D(Vec3f(max[8], 0.0f, max[8]), n[16]), // right-depth
					Plane3D(Vec3f(min[8], 0.0f, min[8]), n[17]), // left-front
			};

			return result;
		}

		///<summary>
		/// Get the center of k-DOP bounding volumne
		///</summary>
		API_INTERFACE inline Vec3f centerOfBoundingVolume() override;

		/// <summary>
		/// Translate the k-DOP
		/// </summary>
		API_INTERFACE DOP18* translate(float xAxis, float yAxis, float zAxis) override;

		/// <summary>
		/// k-DOP is never rotated! Use OBB instead.
		/// </summary>
		API_INTERFACE DOP18* rotate(float angleInRadians, float xAxis, float yAxis, float zAxis) override;

		/// <summary>
		/// Scale the k-DOP
		/// </summary>
		API_INTERFACE DOP18* scale(float xAxis, float yAxis, float zAxis) override;

		/// <summary>
		/// Get model view of k-DOP
		/// </summary>
		API_INTERFACE Mat3f modelView() override;

		/// <summary>
		/// Check collision with another k-DOP
		/// </summary>
		API_INTERFACE CollisionStatus collisionStatus(const DOP18& kDop);

	};

}

#endif // !DOP18_HEADER