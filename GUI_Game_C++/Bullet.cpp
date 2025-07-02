#include "Bullet.h"	
#include "CollisionManager.h"
#include <variant>

// �R���X�g���N�^
Bullet::Bullet(VECTOR pos, VECTOR dir, double radius, double speed, double life, CollisionManager* manager)
	: SphereCollider(pos, radius, manager), 
	m_dir(dir), m_speed(speed), m_life(life), m_manager(manager)
{
	m_color = GetColor(255, 255, 0);
	
	SetRandomColor();
}

// �f�X�g���N�^
Bullet::~Bullet()
{}

// �F�������_���ɐݒ肷��
void Bullet::SetRandomColor()
{
	m_color = GetColor(GetRand(255), GetRand(255), GetRand(255));

	SetIsHitFALSE();
}

// �X�V
void Bullet::Update()
{
	std::get<SphereType>(data).m_spherePos = VAdd(std::get<SphereType>(data).m_spherePos, VScale(m_dir, (float)m_speed));
	SetAABB(); // AABB�̍X�V
	m_life--;
}

// �`��
void Bullet::DrawBullet() const
{
	DrawSphere3D(std::get<SphereType>(data).m_spherePos, (float)std::get<SphereType>(data).m_radius, 8, m_color, m_color, TRUE);

	DrawAABB();
}

// ��������
bool Bullet::IsAlive() const
{
	return m_life > 0;
}
