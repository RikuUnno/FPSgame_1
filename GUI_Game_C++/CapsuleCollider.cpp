#include "CapsuleCollider.h"
#include <cmath>

// コンストラクタ
CapsuleCollider::CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius, CollisionManager* manager)
    : Collider(CapsuleType{top, bottom, height, radius}, manager)
{
    SetAABB();
}

// デストラクタ
CapsuleCollider::~CapsuleCollider()
{}

void CapsuleCollider::SetAABB()
{
    const CapsuleType& capPos = std::get<CapsuleType>(data);

    aabb.min.x = fmin(capPos.m_posTop.x, capPos.m_posBottom.x) - (float)capPos.m_radius;
    aabb.min.y = fmin(capPos.m_posTop.y, capPos.m_posBottom.y) - (float)capPos.m_radius;
    aabb.min.z = fmin(capPos.m_posTop.z, capPos.m_posBottom.z) - (float)capPos.m_radius;

    aabb.max.x = fmax(capPos.m_posTop.x, capPos.m_posBottom.x) + (float)capPos.m_radius;
    aabb.max.y = fmax(capPos.m_posTop.y, capPos.m_posBottom.y) + (float)capPos.m_radius;
    aabb.max.z = fmax(capPos.m_posTop.z, capPos.m_posBottom.z) + (float)capPos.m_radius;
}


