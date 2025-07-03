#include "BoxCollider.h"

// �R���X�g���N�^
BoxCollider::BoxCollider(VECTOR min, VECTOR max, CollisionManager* manager)
	: Collider(BoxType{ min, max }, manager)
{
	AddCollider(manager);

	SetAABB();
}

// �f�X�g���N�^
BoxCollider::~BoxCollider()
{}

// AABB�̐ݒ�
void BoxCollider::SetAABB()
{
	const BoxType& BoxPos = std::get<BoxType>(data);

	aabb.min = BoxPos.min;
	aabb.max = BoxPos.max;
}