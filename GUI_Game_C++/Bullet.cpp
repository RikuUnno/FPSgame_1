#include "Bullet.h"	

// �R���X�g���N�^
Bullet::Bullet(VECTOR pos, VECTOR dir, double radius, double speed, double life)
	: SphereCollider(pos, radius), 
	m_dir(dir), m_speed(speed), m_life(life)
{}

// �f�X�g���N�^
Bullet::~Bullet()
{}

// �X�V
void Bullet::Update()
{
	m_spherePos = VAdd(m_spherePos, VScale(m_dir, (float)m_speed));
	m_life--;
}

// �`��
void Bullet::DrawBullet() const
{
	DrawSphere3D(m_spherePos, (float)m_radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
}

// ��������
bool Bullet::IsAlive() const
{
	return m_life > 0;
}