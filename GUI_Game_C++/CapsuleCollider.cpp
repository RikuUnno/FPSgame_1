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
