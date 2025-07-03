#include "BoxCollider.h"

// コンストラクタ
BoxCollider::BoxCollider(VECTOR min, VECTOR max, CollisionManager* manager)
	: Collider(BoxType{ min, max }, manager)
{
	AddCollider(manager);

	SetAABB();
}

// デストラクタ
BoxCollider::~BoxCollider()
{}

// AABBの設定
void BoxCollider::SetAABB()
{
	const BoxType& BoxPos = std::get<BoxType>(data);

	aabb.min = BoxPos.min;
	aabb.max = BoxPos.max;
}