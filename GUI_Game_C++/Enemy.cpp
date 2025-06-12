#include "Enemy.h"

Enemy::Enemy(VECTOR pos, double height, double radius)
    : CapsuleCollider(VAdd(pos, VGet(0.0f, height, 0.0f)), pos, height, radius) // top // bottom // radius
{}

Enemy::~Enemy()
{}

// 位置更新　基本補m_posButtomをうごかしたらこの関数を呼ぶ（必ず）
void Enemy::SetPosition()
{
    m_posTop = VAdd(m_posBottom, VGet(0, (float)m_height, 0));
}

// 更新
void Enemy::Update() 
{

	SetPosition(); // m_posButtomを変更する際は必ず必用

    Draw();
}

// 描画
void Enemy::Draw() 
{
    DrawCapsule3D(m_posBottom, m_posTop, (float)m_radius, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), TRUE);
}