#include "OBB.h"

OBB::OBB(const Vec3f& center, const Vec3f& halfWidth)
{
	this->center = center;
	this->halfWidth = halfWidth;
	this->orientation = Mat3f::identity();
}

ColisionStatus OBB::colisionStatus(const OBB& obb)
{
	float ra, rb; 
	Mat3f R, AbsR; 
	
	// Compute rotation matrix expressing b in a’s coordinate frame 
	for (int i = 0; i < MAT3_ROWSIZE; i++) 
		for (int j = 0; j < MAT3_ROWSIZE; j++)
			R[i * MAT3_ROWSIZE + j] = orientation.getAxis(i).dot(obb.orientation.getAxis(j));

	// Compute translation vector t 
	Vec3f t = obb.center - center; 

	// Bring translation into a’s coordinate frame 
	t = Vec3f(t.dot(orientation.xAxis()), t.dot(orientation.yAxis()), t.dot(orientation.zAxis()));


	// Compute common subexpressions. Add in an epsilon term to 
	// counteract arithmetic errors when two edges are parallel and 
	// their cross product is (near) null (see text for details) 
	for (int i = 0; i < MAT3_SIZE; i++) 
			AbsR[i] = std::fabsf(R[i]) + DefaultErrorMargin;  // + EPSILON
	
	// Test axes L = A0, L = A1, L = A2 
	for (int i = 0; i < MAT3_ROWSIZE; i++) 
	{ 
		ra = halfWidth[i]; 
		rb = obb.halfWidth[0] * AbsR[i * MAT3_ROWSIZE] 
			+ obb.halfWidth[1] * AbsR[i * MAT3_ROWSIZE + 1] 
			+ obb.halfWidth[2] * AbsR[i * MAT3_ROWSIZE + 2];
		
		if (std::fabs(t[i]) > ra + rb) 
			return ColisionStatus::OUTSIDE; 
	} 
	
	// Test axes L = B0, L = B1, L = B2 
	for (int i = 0; i < MAT3_ROWSIZE; i++)
	{ 
		ra = halfWidth[0] * AbsR[i] 
			+ halfWidth[1] * AbsR[MAT3_ROWSIZE + i] 
			+ halfWidth[2] * AbsR[TWO_MAT3_ROWSIZE + i];
		rb = obb.halfWidth[i];
		
		if (std::fabsf(t[0] * R[i] + t[1] * R[MAT3_ROWSIZE + i] + t[2] * R[TWO_MAT3_ROWSIZE + i]) > ra + rb)
			return ColisionStatus::OUTSIDE;
	} 
	
	// Test axis L = A0 x B0 
	ra = halfWidth[1] * AbsR[TWO_MAT3_ROWSIZE] + halfWidth[2] * AbsR[MAT3_ROWSIZE];
	rb = obb.halfWidth[1] * AbsR[2] + obb.halfWidth[2] * AbsR[1];
	
	if (std::fabsf(t[2] * R[MAT3_ROWSIZE] - t[1] * R[TWO_MAT3_ROWSIZE]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A0 x B1 
	ra = halfWidth[1] * AbsR[7] + halfWidth[2] * AbsR[4];
	rb = obb.halfWidth[0] * AbsR[2] + obb.halfWidth[2] * AbsR[0];
	
	if (std::fabsf(t[2] * R[4] - t[1] * R[7]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A0 x B2 
	ra = halfWidth[1] * AbsR[8] + halfWidth[2] * AbsR[5];
	rb = obb.halfWidth[0] * AbsR[1] + obb.halfWidth[1] * AbsR[0];
	
	if (std::fabsf(t[2] * R[MAT3_ROWSIZE + 2] - t[1] * R[8]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A1 x B0 
	ra = halfWidth[0] * AbsR[TWO_MAT3_ROWSIZE] + halfWidth[2] * AbsR[0];
	rb = obb.halfWidth[1] * AbsR[5] + obb.halfWidth[2] * AbsR[4];

	if (std::fabsf(t[0] * R[TWO_MAT3_ROWSIZE] - t[2] * R[0]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A1 x B1 
	ra = halfWidth[0] * AbsR[7] + halfWidth[2] * AbsR[1];
	rb = obb.halfWidth[0] * AbsR[5] + obb.halfWidth[2] * AbsR[MAT3_ROWSIZE];
	
	if (std::fabsf(t[0] * R[7] - t[2] * R[1]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A1 x B2 
	ra = halfWidth[0] * AbsR[8] + halfWidth[2] * AbsR[2];
	rb = obb.halfWidth[0] * AbsR[4] + obb.halfWidth[1] * AbsR[MAT3_ROWSIZE];
	
	if (std::fabsf(t[0] * R[8] - t[2] * R[2]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A2 x B0 
	ra = halfWidth[0] * AbsR[MAT3_ROWSIZE] + halfWidth[1] * AbsR[0];
	rb = obb.halfWidth[1] * AbsR[8] + obb.halfWidth[2] * AbsR[7];
	
	if (std::fabsf(t[1] * R[0] - t[0] * R[MAT3_ROWSIZE]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A2 x B1 
	ra = halfWidth[0] * AbsR[4] + halfWidth[1] * AbsR[1];
	rb = obb.halfWidth[0] * AbsR[8] + obb.halfWidth[2] * AbsR[TWO_MAT3_ROWSIZE];
	
	if (std::fabsf(t[1] * R[1] - t[0] * R[4]) > ra + rb)
		return ColisionStatus::OUTSIDE;
	
	// Test axis L = A2 x B2 
	ra = halfWidth[0] * AbsR[5] + halfWidth[1] * AbsR[2];
	rb = obb.halfWidth[0] * AbsR[7] + obb.halfWidth[1] * AbsR[TWO_MAT3_ROWSIZE];
	
	if (std::fabsf(t[1] * R[2] - t[0] * R[5]) > ra + rb)
		return ColisionStatus::OUTSIDE;
		
	return ColisionStatus::INSIDE; // Since no separating axis is found, the OBBs must be intersecting 
}