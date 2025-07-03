#pragma once
#include <DxLib.h>
#include "Collider.h"

class BoxCollider : public Collider
{
protected:
	BoxCollider(VECTOR min, VECTOR max, CollisionManager* manager); // コンストラクタ
	virtual ~BoxCollider(); // デストラクタ

public:
	VECTOR GetBoxPosMin() { return std::get<BoxType>(data).min; } // m_spherePosのゲッター
	VECTOR GetBoxPosMax() { return std::get<BoxType>(data).max; } // m_radiusのゲッター

	void SetAABB() override;
};