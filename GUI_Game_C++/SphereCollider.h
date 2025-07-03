#pragma once
#include <DxLib.h>
#include "Collider.h"

class SphereCollider : public Collider
{
protected:
	SphereCollider(VECTOR spherePos, double redius, CollisionManager* manager); // コンストラクタ
	virtual ~SphereCollider(); // デストラクタ

public:
	VECTOR GetSpherePos() { return std::get<SphereType>(data).m_spherePos; } // m_spherePosのゲッター
	double GetSphereRadius() { return std::get<SphereType>(data).m_radius; } // m_radiusのゲッター

	void SetAABB() override;
};
