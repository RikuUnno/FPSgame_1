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

// 当たり判定 (球用)
bool CapsuleCollider::CheckCollision(const VECTOR& spherePos, double sphereRadius) const {
    VECTOR seg = VSub(m_posTop, m_posBottom);
    VECTOR proj = VSub(spherePos, m_posBottom);

    double segLenSq = VDot(seg, seg);
    double t = static_cast<double>(VDot(proj, seg)) / segLenSq;
    t = std::fmax(0.0, std::fmin(1.0, t));

    VECTOR closest = VAdd(m_posBottom, VScale(seg, (float)t));
    double distSq = VSquareSize(VSub(spherePos, closest));

    double totalRadius = m_radius + sphereRadius;
    return distSq <= (totalRadius * totalRadius);
}