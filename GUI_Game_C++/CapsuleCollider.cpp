#include "CapsuleCollider.h"
#include <cmath>

// コンストラクタ
CapsuleCollider::CapsuleCollider(VECTOR top, VECTOR bottom, double radius)
    : m_posTop(top), m_posBottom(bottom), m_radius(radius) {}

// デストラクタ
CapsuleCollider::~CapsuleCollider()
{}

// 形状変化の更新用関数
void CapsuleCollider::SetCapsule(VECTOR top, VECTOR bottom, double radius) {
    m_posTop = top;
    m_posBottom = bottom;
    m_radius = radius;
}

// 位置更新用（下端から上端を計算）
void CapsuleCollider::SetPosition(VECTOR basePos, double height) {
    m_posBottom = basePos;
    m_posTop = VAdd(basePos, VGet(0, (float)height, 0));
}
