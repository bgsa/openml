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
	private:
		void fixTopDegeneration(const Plane3D* planes);
		void fixBottomDegeneration(const Plane3D* planes);
		void fixLeftDegeneration(const Plane3D* planes);
		void fixRightDegeneration(const Plane3D* planes);
		void fixFrontDegeneration(const Plane3D* planes);
		void fixDepthDegeneration(const Plane3D* planes);

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
		API_INTERFACE inline Plane3D* planes();

		///<summary>
		/// Get the center of k-DOP bounding volumne
		///</summary>
		API_INTERFACE inline Vec3f centerOfBoundingVolume() const override;

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

		/// <summary>
		/// Fix degenerated 18-DOP pulling their planes on the right position
		/// </summary>
		API_INTERFACE void fixDegenerations();

	};

}

#endif // !DOP18_HEADER