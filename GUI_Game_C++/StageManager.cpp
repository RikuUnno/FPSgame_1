#include "StageManager.h"

StageManager::StageManager()
{
    stages.reserve(50); // 生成するステージのブロック数による
}

StageManager::~StageManager()
{}

void StageManager::Init(CollisionManager* cm)
{
    // 地面
    stages.emplace_back(VGet(-50, 0, -50), VGet(50, 1, 50), GetColor(100, 100, 255), cm);

    // ブロック
    stages.emplace_back(VGet(-10, 1, -10), VGet(10, 3, 10), GetColor(180, 100, 100), cm);
    stages.emplace_back(VGet(15, 1, 5), VGet(25, 4, 15), GetColor(100, 180, 100), cm);

    // 壁
    stages.emplace_back(VGet(-50, 0, -50), VGet(-49, 10, 50), GetColor(150, 150, 150), cm);
    stages.emplace_back(VGet(49, 0, -50), VGet(50, 10, 50), GetColor(150, 150, 150), cm);
}

// 更新
void StageManager::Update()
{
    for (auto& stage : stages) {
        stage.Update();
    }
}