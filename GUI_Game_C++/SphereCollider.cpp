#include "SphereCollider.h"

// �R���X�g���N�^
SphereCollider::SphereCollider(VECTOR spherePos, double redius)
	: m_spherePos(spherePos), m_radius(redius)
{
	m_isHit = false; // �������Ă����ture
};

// �f�X�g���N�^
SphereCollider::~SphereCollider()
{};

