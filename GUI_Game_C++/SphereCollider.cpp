#include "SphereCollider.h"

// �R���X�g���N�^
SphereCollider::SphereCollider(VECTOR spherePos, double redius, CollisionManager* manager)
	: Collider(SphereType{ spherePos, redius }, manager)
{
	SetAABB();
};

// �f�X�g���N�^
SphereCollider::~SphereCollider()
{};

// AABB�̐ݒ�
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
