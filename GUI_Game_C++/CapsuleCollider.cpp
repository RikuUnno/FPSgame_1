#include "CapsuleCollider.h"
#include <cmath>

// コンストラクタ
CapsuleCollider::CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius)
    : m_posTop(top), m_posBottom(bottom), m_height(height), m_radius(radius)
{
    m_isHit = false; // 当たっていればture
}

// デストラクタ
CapsuleCollider::~CapsuleCollider()
{}

