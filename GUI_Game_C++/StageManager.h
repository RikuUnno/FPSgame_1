#pragma once
#include <vector>
#include "Stage.h"

class StageManager {
private:
    std::vector<Stage> stages; // �X�e�[�W�̃u���b�N�i�Ǔ��j�̊Ǘ��p

public:
    StageManager();
    virtual ~StageManager();

public:
    void Init(CollisionManager* cm); // ��������
    void Update(); // �X�V
};