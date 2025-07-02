#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(const BoxType& box, CollisionManager* manager)
	: type(ColliderType::Box), data(box), m_manager(manager)
{
	m_isHit = false;
	aabb = { VGet(0, 0, 0), VGet(0, 0, 0) };
}

Collider::Collider(const SphereType& sphere, CollisionManager* manager)
	: type(ColliderType::Sphere), data(sphere), m_manager(manager)
{
	m_isHit = false;
	aabb = { VGet(0, 0, 0), VGet(0, 0, 0) };
}

Collider::Collider(const CapsuleType& capsule, CollisionManager* manager)
	: type(ColliderType::Capsule), data(capsule), m_manager(manager)
{
	m_isHit = false;
	aabb = { VGet(0, 0, 0), VGet(0, 0, 0) };
}

Collider::~Collider()
{
    m_manager->DeleteCollider(this);
}

// m_isHitのセッター　true
void Collider::SetIsHitTRUE()
{
	m_isHit = true;
}

// m_isHitのセッター　false
void Collider::SetIsHitFALSE()
{
	m_isHit = false;
}

void Collider::AddCollider(CollisionManager* manager)
{
	manager->GetColliderList().push_back(this);
}

void Collider::DrawAABB() const
{
    int color = GetColor(255, 255, 255);

    VECTOR p[8] = {
        VGet(aabb.min.x, aabb.min.y, aabb.min.z),
        VGet(aabb.max.x, aabb.min.y, aabb.min.z),
        VGet(aabb.max.x, aabb.max.y, aabb.min.z),
        VGet(aabb.min.x, aabb.max.y, aabb.min.z),
        VGet(aabb.min.x, aabb.min.y, aabb.max.z),
        VGet(aabb.max.x, aabb.min.y, aabb.max.z),
        VGet(aabb.max.x, aabb.max.y, aabb.max.z),
        VGet(aabb.min.x, aabb.max.y, aabb.max.z)
    };

    // 線を描画
    DrawLine3D(p[0], p[1], color); DrawLine3D(p[1], p[2], color);
    DrawLine3D(p[2], p[3], color); DrawLine3D(p[3], p[0], color);
    DrawLine3D(p[4], p[5], color); DrawLine3D(p[5], p[6], color);
    DrawLine3D(p[6], p[7], color); DrawLine3D(p[7], p[4], color);
    DrawLine3D(p[0], p[4], color); DrawLine3D(p[1], p[5], color);
    DrawLine3D(p[2], p[6], color); DrawLine3D(p[3], p[7], color);
}