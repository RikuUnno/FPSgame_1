#include "Enemy.h"

Enemy::Enemy(VECTOR pos, double height, double radius)
    : CapsuleCollider(                            // ← ここを追加
        VAdd(pos, VGet(0.0f, height, 0.0f)),   // top
        pos,                                   // bottom
        radius),                               // radius
    m_velocity(VGet(0, 0, 0)),
    m_height(height)
{
    SetPosition(pos, height);  // カプセルの上下端を初期化
    m_radius = radius;
}

Enemy::~Enemy()
{}

void Enemy::Update() 
{
    Draw();
}

void Enemy::Draw() 
{
    DrawCapsule3D(m_posBottom, m_posTop, (float)m_radius, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), TRUE);
}