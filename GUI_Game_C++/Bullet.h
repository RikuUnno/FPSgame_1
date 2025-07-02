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
	unsigned int m_color; // 色

	CollisionManager* m_manager;

public:
	// コンストラクタ
	Bullet(VECTOR pos, VECTOR dir, double radius, double speed, double life, CollisionManager* manager);

	// デストラクタ
	virtual ~Bullet();

	// 色をランダムに設定する
	void SetRandomColor();

	// 更新
	void Update();

	// 描画
	void DrawBullet() const; 

	// 生存判定
	bool IsAlive() const;
};