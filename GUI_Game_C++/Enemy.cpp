#include "Enemy.h"

Enemy::Enemy(VECTOR pos, double height, double radius)
    : CapsuleCollider(VAdd(pos, VGet(0.0f, height, 0.0f)), pos, height, radius) // top // bottom // radius
{}

Enemy::~Enemy()
{}

// �ʒu�X�V�@��{��m_posButtom�������������炱�̊֐����Ăԁi�K���j
void Enemy::SetPosition()
{
    m_posTop = VAdd(m_posBottom, VGet(0, (float)m_height, 0));
}

// �X�V
void Enemy::Update() 
{

	SetPosition(); // m_posButtom��ύX����ۂ͕K���K�p

    Draw();
}

// �`��
void Enemy::Draw() 
{
    DrawCapsule3D(m_posBottom, m_posTop, (float)m_radius, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), TRUE);
}