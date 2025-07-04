#pragma once
#include <vector>
#include "Stage.h"

class StageManager {
private:
    std::vector<Stage> stages; // ステージのブロック（壁等）の管理用

public:
    StageManager();
    virtual ~StageManager();

public:
    void Init(CollisionManager* cm); // 初期生成
    void Update(); // 更新
};