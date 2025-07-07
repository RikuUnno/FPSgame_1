#pragma once
#include <vector>
#include "Enemy.h"

struct EnemySpawner // �G�̃X�|�[���ʒu
{
	VECTOR position;     // �X�|�[���ʒu
	double minX, maxX;    // ���ړ��͈�
};

class EnemyManager
{
private:
	std::vector<Enemy> enemys; // enemy�̊Ǘ��p

	std::vector<EnemySpawner> spawners; // �X�|�i�[�̊Ǘ�

	CollisionManager* m_cm;
public:
	EnemyManager(CollisionManager*);

	virtual ~EnemyManager();

public:
	void InitSpawners(); // �X�|�i�[�����o�^����

	void SpawnEnemy(); // �G���X�|�[������

	void Update();     // �G�̍X�V�{���X�|�[��

	bool IsEnemyDead() const;

};