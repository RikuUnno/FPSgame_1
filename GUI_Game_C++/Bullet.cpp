#include "Bullet.h"	
#include "CollisionManager.h"
#include <variant>

// コンストラクタ
Bullet::Bullet(VECTOR pos, VECTOR dir, double radius, double speed, double life, CollisionManager* manager)
	: SphereCollider(pos, radius, manager), 
	m_dir(dir), m_speed(speed), m_life(life), m_manager(manager)
{
	m_color = GetColor(255, 255, 0);
	
	SetRandomColor();
}

// デストラクタ
Bullet::~Bullet()
{}

// 色をランダムに設定する
void Bullet::SetRandomColor()
{
	m_color = GetColor(GetRand(255), GetRand(255), GetRand(255));

	SetIsHitFALSE();
}

// 更新
void Bullet::Update()
{
	//SphereType* a = std::get_if<SphereType>(&data);
	//SphereType a = std::get<SphereType>(data);
	//SphereType& a = std::get<SphereType>(data);


	std::get_if<SphereType>(&data)->m_spherePos = VAdd(std::get_if<SphereType>(&data)->m_spherePos, VScale(m_dir, (float)m_speed));
	//std::get<SphereType>(data).m_spherePos = VAdd(std::get_if<SphereType>(&data)->m_spherePos, VScale(m_dir, (float)m_speed));
	SetAABB(); // AABBの更新
	m_life--;
}

// 描画
void Bullet::DrawBullet() const
{
	DrawSphere3D(std::get_if<SphereType>(&data)->m_spherePos, (float)std::get_if<SphereType>(&data)->m_radius, 8, m_color, m_color, TRUE);

#ifdef _DEBUG
	DrawAABB(); // AABBの表示（Debug）
#endif // _DEBUG
}

// 生存判定
bool Bullet::IsAlive() const
{
	return m_life > 0;
}
