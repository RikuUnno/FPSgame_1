#include "Enemy.h"

Enemy::Enemy(VECTOR pos, double height, double radius, double moveMinX, double moveMaxX, CollisionManager* manager)
    : CapsuleCollider(VAdd(pos, VGet(0.0f, (float)height, 0.0f)), pos, height, radius, manager), // top // bottom // radius
    m_minX(moveMinX), m_maxX(moveMaxX)
{
    m_enemyColor = GetColor(255, 0, 0);
    m_speed = 0.08;
    m_movingRight = false;
    m_isDead = false;
}

Enemy::Enemy(const Enemy& other)
    :CapsuleCollider(other.GetCapsule()->m_posTop, other.GetCapsule()->m_posBottom, other.GetCapsule()->m_height, other.GetCapsule()->m_radius, other.m_manager),
    m_minX(other.m_minX), m_maxX(other.m_maxX)
{
    m_enemyColor = other.m_enemyColor;
    m_speed = other.m_speed;
    m_movingRight = other.m_movingRight;
    m_isDead = other.m_isDead;
}

Enemy::~Enemy()
{}

// 位置更新　基本補m_posButtomをうごかしたらこの関数を呼ぶ（必ず）
void Enemy::SetPosition()
{
    std::get<CapsuleType>(data).m_posTop = VAdd(std::get<CapsuleType>(data).m_posBottom, VGet(0, (float)std::get<CapsuleType>(data).m_height, 0));
}

// 色の変更
void Enemy::SetRandomColor()
{
        m_enemyColor = GetColor(GetRand(255), GetRand(255), GetRand(255));
        m_isHit = false; // 最後にはfalseに戻す
}

// 更新
void Enemy::Update() 
{
    Move(); // 横移動

    //SetRandomColor();

    SetAABB(); // AABBの更新 

#ifdef _DEBUG
    DrawAABB(); // AABBの表示（Debug）
#endif // _DEBUG

    Draw();
}

// 描画
void Enemy::Draw() 
{
    DrawCapsule3D(std::get<CapsuleType>(data).m_posBottom, std::get<CapsuleType>(data).m_posTop, (float)std::get<CapsuleType>(data).m_radius, 8, m_enemyColor, m_enemyColor, TRUE);
}

void Enemy::Move()
{
    VECTOR& bottom = std::get<CapsuleType>(data).m_posBottom;

    if (m_movingRight)
    {
        bottom.x += (float)m_speed;
        if (bottom.x >= m_maxX) m_movingRight = false;
    }
    else
    {
        bottom.x -= (float)m_speed;
        if (bottom.x <= m_minX) m_movingRight = true;
    }

    SetPosition(); // top位置を更新
}

void Enemy::OnCollisionEnter(Collider* other) 
{
    // プレイヤーの弾と衝突
    if (other->GetType() == ColliderType::Sphere) {
    Kill();
    }
}