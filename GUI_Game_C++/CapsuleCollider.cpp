#include "CapsuleCollider.h"
#include <cmath>

// �R���X�g���N�^
CapsuleCollider::CapsuleCollider(VECTOR top, VECTOR bottom, double radius)
    : m_posTop(top), m_posBottom(bottom), m_radius(radius) {}

// �f�X�g���N�^
CapsuleCollider::~CapsuleCollider()
{}

// �`��ω��̍X�V�p�֐�
void CapsuleCollider::SetCapsule(VECTOR top, VECTOR bottom, double radius) {
    m_posTop = top;
    m_posBottom = bottom;
    m_radius = radius;
}

// �ʒu�X�V�p�i���[�����[���v�Z�j
void CapsuleCollider::SetPosition(VECTOR basePos, double height) {
    m_posBottom = basePos;
    m_posTop = VAdd(basePos, VGet(0, (float)height, 0));
}

// �����蔻�� (���p)
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