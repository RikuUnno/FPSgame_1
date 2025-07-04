#include "SphereCollider.h"

// コンストラクタ
SphereCollider::SphereCollider(VECTOR spherePos, double redius, CollisionManager* manager)
	: Collider(SphereType{ spherePos, redius }, manager)
{
	SetAABB();
};

// デストラクタ
SphereCollider::~SphereCollider()
{};

// AABBの設定
void SphereCollider::SetAABB()
{
	const SphereType& SphePos = std::get<SphereType>(data);

	aabb.min = VGet(
		SphePos.m_spherePos.x - (float)SphePos.m_radius,
		SphePos.m_spherePos.y - (float)SphePos.m_radius,
		SphePos.m_spherePos.z - (float)SphePos.m_radius
	);

	aabb.max = VGet(
		SphePos.m_spherePos.x + (float)SphePos.m_radius,
		SphePos.m_spherePos.y + (float)SphePos.m_radius,
		SphePos.m_spherePos.z + (float)SphePos.m_radius
	);	
}
