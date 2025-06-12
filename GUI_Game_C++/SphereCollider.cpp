#include "SphereCollider.h"

// コンストラクタ
SphereCollider::SphereCollider(VECTOR spherePos, double redius)
	: m_spherePos(spherePos), m_radius(redius)
{
	m_isHit = false; // 当たっていればture
};

// デストラクタ
SphereCollider::~SphereCollider()
{};

