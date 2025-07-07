#pragma once
#include <vector>
#include "Enemy.h"

struct EnemySpawner // 敵のスポーン位置
{
	VECTOR position;     // スポーン位置
	double minX, maxX;    // 横移動範囲
};

class EnemyManager
{
private:
	std::vector<Enemy> enemys; // enemyの管理用

	std::vector<EnemySpawner> spawners; // スポナーの管理

	CollisionManager* m_cm;
public:
	EnemyManager(CollisionManager*);

	virtual ~EnemyManager();

public:
	void InitSpawners(); // スポナーだけ登録する

	void SpawnEnemy(); // 敵をスポーンする

	void Update();     // 敵の更新＋リスポーン

	bool IsEnemyDead() const;

};