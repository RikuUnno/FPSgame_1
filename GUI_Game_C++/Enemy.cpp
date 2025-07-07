#include "Enemy.h"

Enemy::Enemy(VECTOR pos, double height, double radius, double moveMinX, double moveMaxX, CollisionManager* manager)
    : CapsuleCollider(VAdd(pos, VGet(0.0f, (float)height, 0.0f)), pos, height, radius, manager), // top // bottom // radius
    m_minX(moveMinX), m_maxX(moveMaxX)
{
    EnemyColor = GetColor(255, 0, 0);
    m_speed = 0.08;
    m_movingRight = false;
    m_isDead = false;
}

Enemy::~Enemy()
{}

// �ʒu�X�V�@��{��m_posButtom�������������炱�̊֐����Ăԁi�K���j
void Enemy::SetPosition()
{
    std::get<CapsuleType>(data).m_posTop = VAdd(std::get<CapsuleType>(data).m_posBottom, VGet(0, (float)std::get<CapsuleType>(data).m_height, 0));
}

// �F�̕ύX
void Enemy::SetRandomColor()
{
        EnemyColor = GetColor(GetRand(255), GetRand(255), GetRand(255));
        m_isHit = false; // �Ō�ɂ�false�ɖ߂�
}

// �X�V
void Enemy::Update() 
{
    Move(); // ���ړ�

    //SetRandomColor();

    SetAABB(); // AABB�̍X�V 

#ifdef _DEBUG
    DrawAABB(); // AABB�̕\���iDebug�j
#endif // _DEBUG

    Draw();
}

// �`��
void Enemy::Draw() 
{
    DrawCapsule3D(std::get<CapsuleType>(data).m_posBottom, std::get<CapsuleType>(data).m_posTop, (float)std::get<CapsuleType>(data).m_radius, 8, EnemyColor, EnemyColor, TRUE);
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

    SetPosition(); // top�ʒu���X�V
}

void Enemy::OnCollisionEnter(Collider* other) 
{
    // �v���C���[�̒e�ƏՓ�
    if (other->GetType() == ColliderType::Sphere) {
    Kill();
    }
}