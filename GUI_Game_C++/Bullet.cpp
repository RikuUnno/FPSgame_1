#include "Bullet.h"	

// コンストラクタ
Bullet::Bullet(VECTOR pos, VECTOR dir, double radius, double speed, double life)
	: SphereCollider(pos, radius), 
	m_dir(dir), m_speed(speed), m_life(life)
{}

// デストラクタ
Bullet::~Bullet()
{}

// 更新
void Bullet::Update()
{
	m_spherePos = VAdd(m_spherePos, VScale(m_dir, (float)m_speed));
	m_life--;
}

// 描画
void Bullet::DrawBullet() const
{
	DrawSphere3D(m_spherePos, (float)m_radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
}

// 生存判定
bool Bullet::IsAlive() const
{
	return m_life > 0;
}