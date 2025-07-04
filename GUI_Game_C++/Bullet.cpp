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

Bullet::Bullet(const Bullet& other)
	: SphereCollider(other.GetSphere()->m_spherePos, other.GetSphere()->m_radius, other.m_manager),
	m_dir(other.m_dir),
	m_speed(other.m_speed),
	m_life(other.m_life),
	m_color(other.m_color),
	m_manager(other.m_manager)
{
#ifdef _DEBUG
	printfDx("cpy");
#endif // _DEBUG
}



// �f�X�g���N�^
Bullet::~Bullet()
{}

// �F�������_���ɐݒ肷��
void Bullet::SetRandomColor()
{
	m_color = GetColor(GetRand(255), GetRand(255), GetRand(255));
}

// �X�V
void Bullet::Update()
{
	SphereType* sphere = std::get_if<SphereType>(&data);
	sphere->m_spherePos = VAdd(sphere->m_spherePos, VScale(m_dir, (float)m_speed));
	SetAABB(); // AABB�̍X�V
	m_life--;
}

// �`��
void Bullet::DrawBullet() const
{
	const SphereType sphere = std::get<SphereType>(data);
	DrawSphere3D(sphere.m_spherePos, (float)sphere.m_radius, 8, m_color, m_color, TRUE);

#ifdef _DEBUG
	DrawAABB(); // AABB�̕\���iDebug�j
#endif // _DEBUG
}

// ��������
bool Bullet::IsAlive() const
{
	return m_life > 0;
}
