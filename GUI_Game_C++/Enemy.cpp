#include "Enemy.h"

Enemy::Enemy(VECTOR pos, double height, double radius, CollisionManager* manager)
    : CapsuleCollider(VAdd(pos, VGet(0.0f, (float)height, 0.0f)), pos, height, radius, manager) // top // bottom // radius
{
    EnemyColor = GetColor(255, 0, 0);
}

Enemy::~Enemy()
{}

// 位置更新　基本補m_posButtomをうごかしたらこの関数を呼ぶ（必ず）
void Enemy::SetPosition()
{
    std::get<CapsuleType>(data).m_posTop = VAdd(std::get<CapsuleType>(data).m_posBottom, VGet(0, (float)std::get<CapsuleType>(data).m_height, 0));
}

void Enemy::SetRandomColor()
{
    if (m_isHit == true)
    {

        EnemyColor = GetColor(GetRand(255), GetRand(255), GetRand(255));

        m_isHit = false; // 最後にはfalseに戻す
    }
}

// 更新
void Enemy::Update() 
{
	SetPosition(); // m_posButtomを変更する際は必ず必用

    SetRandomColor();

    SetAABB(); // AABBの更新 

#ifdef _DEBUG
    DrawAABB(); // AABBの表示（Debug）
#endif // _DEBUG

    Draw();
}

// 描画
void Enemy::Draw() 
{
    DrawCapsule3D(std::get<CapsuleType>(data).m_posBottom, std::get<CapsuleType>(data).m_posTop, (float)std::get<CapsuleType>(data).m_radius, 8, EnemyColor, EnemyColor, TRUE);
}