#include "CapsuleCollider.h"
#include <cmath>

// �R���X�g���N�^
CapsuleCollider::CapsuleCollider(VECTOR top, VECTOR bottom, double radius)
    : m_posTop(top), m_posBottom(bottom), m_radius(radius) 
{}

// �f�X�g���N�^
CapsuleCollider::~CapsuleCollider()
{}

