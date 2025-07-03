#include "Enemy.h"

Enemy::Enemy(VECTOR pos, double height, double radius, CollisionManager* manager)
    : CapsuleCollider(VAdd(pos, VGet(0.0f, (float)height, 0.0f)), pos, height, radius, manager) // top // bottom // radius
{
    EnemyColor = GetColor(255, 0, 0);
}

Enemy::~Enemy()
{}

// �ʒu�X�V�@��{��m_posButtom�������������炱�̊֐����Ăԁi�K���j
void Enemy::SetPosition()
{
    std::get<CapsuleType>(data).m_posTop = VAdd(std::get<CapsuleType>(data).m_posBottom, VGet(0, (float)std::get<CapsuleType>(data).m_height, 0));
}

void Enemy::SetRandomColor()
{
    if (m_isHit == true)
    {

        EnemyColor = GetColor(GetRand(255), GetRand(255), GetRand(255));

        m_isHit = false; // �Ō�ɂ�false�ɖ߂�
    }
}

// �X�V
void Enemy::Update() 
{
	SetPosition(); // m_posButtom��ύX����ۂ͕K���K�p

    SetRandomColor();

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