#pragma once

#include <DxLib.h>

class SphereCollider
{
protected:
	VECTOR m_spherePos; // 球の中心点
	double m_radius;	// 円の半径
	bool m_isHit;       // 衝突したらtrue

protected:
	SphereCollider(VECTOR spherePos, double redius); // コンストラクタ
	virtual ~SphereCollider(); // デストラクタ

public:
	VECTOR GetSpherePos() { return m_spherePos; } // m_spherePosのゲッター
	double GetSphereRadius() { return m_radius; } // m_radiusのゲッター
	bool GetIsHit() { return m_isHit; }			  // m_isHitのゲッター

	bool SetIsHitTRUE() { return m_isHit = true; }   // m_isHitのセッター　true
	bool SetIsHitFALSE() { return m_isHit = false; } // m_isHitのセッター  false
};
