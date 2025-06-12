#pragma once

#include <DxLib.h>

class SphereCollider
{
protected:
	VECTOR m_spherePos; // 球の中心点
	double m_radius; // 円の半径

protected:
	SphereCollider(VECTOR spherePos, double redius); // コンストラクタ
	virtual ~SphereCollider(); // デストラクタ

	bool HitCheckCollider();

public:
	VECTOR GetSpherePos() { return m_spherePos; } // m_spherePosのゲッター
	double GetSphereRadius() { return m_radius; } // m_radiusのゲッター
};
