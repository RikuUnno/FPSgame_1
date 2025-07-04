#include "StageManager.h"

StageManager::StageManager()
{
    stages.reserve(50); // 生成するステージのブロック数による
}

StageManager::~StageManager()
{}

void StageManager::Init(CollisionManager* cm)
{
    // 地面（明るめの落ち着いたグレー）
    stages.emplace_back(
        VGet(-100, 0, -100), VGet(100, 1, 100),
        GetColor(110, 110, 110), cm
    );

    // 奥の壁（しっかり明るめの灰色、プレイヤーが見失わない）
    stages.emplace_back(
        VGet(-100, 1, 99), VGet(100, 20, 100),
        GetColor(160, 160, 160), cm
    );

    // 左の壁（中間グレー：真っ黒すぎない、影になじむ）
    stages.emplace_back(
        VGet(-100, 1, -100), VGet(-98, 20, 100),
        GetColor(70, 70, 70), cm
    );

    // 右の壁（左と同じトーン）
    stages.emplace_back(
        VGet(98, 1, -100), VGet(100, 20, 100),
        GetColor(70, 70, 70), cm
    );
}

// 更新
void StageManager::Update()
{
    for (auto& stage : stages) {
        stage.Update();
    }
}