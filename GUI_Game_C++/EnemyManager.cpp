#include "EnemyManager.h"
#include "GameManager.h"
#include <algorithm>

EnemyManager::EnemyManager(CollisionManager* cm)
    :m_cm(cm)
{
	enemys.reserve(2);
}

EnemyManager::~EnemyManager()
{}

void EnemyManager::InitSpawners()
{
    spawners = {
        { VGet(-45, 3, 100), -45, -30 },      // ���ݒu�ꏊ���̗���
        { VGet(-5, 3, 75), -16, -5 },         // �ݒu�ꏊ�̒���
        { VGet(13, 3, 75), 13, 25 },          // �ݒu�ꏊ�̒���
        { VGet(-20, 23, 130), -20, -10},      // ����̍�  
        { VGet(37, 23, 130), 23, 37}          // ����̉E
    };
}

void EnemyManager::SpawnEnemy()
{
    if (spawners.empty()) return;

    int index = GetRand((int)spawners.size() - 1);
    const auto& sp = spawners[index];

    enemys.emplace_back(sp.position, 7.0, 2.0, sp.minX, sp.maxX, m_cm);
}

void EnemyManager::Update()
{
    std::erase_if(enemys, [](const Enemy& e) {
        return e.IsDead();
        });

    if (IsEnemyDead())
    {
        SpawnEnemy(); // �V�����X�|�[��
        GameManager::GetInstance().OnEnemyKilled();  // +100�_�̉��_����
    }

    for (auto& enemy : enemys)
    {
        enemy.Update();
    }
}

bool EnemyManager::IsEnemyDead() const
{
    return enemys.empty(); // �G�����Ȃ���΁u���񂾁v
}
