#pragma once
#include "DxLib.h"
#include "SphereCollider.h"

class Bullet
	: public SphereCollider
{
private:
	VECTOR m_dir; // 進行方向（正規化）
	double m_speed; // 移動速度
	double m_life; // 寿命(フレーム数)

public:
	// コンストラクタ
	Bullet(VECTOR pos, VECTOR dir, double radius = 1.0, double speed = 1.0, double life = 300.0);

	// デストラクタ
	virtual ~Bullet();

	// 更新
	void Update();

	// 描画
	void DrawBullet() const; 

	// 生存判定
	bool IsAlive() const;
};