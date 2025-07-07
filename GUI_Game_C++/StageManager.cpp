#include "StageManager.h"

StageManager::StageManager()
{
    stages.reserve(50); // ��������X�e�[�W�̃u���b�N���ɂ��
}

StageManager::~StageManager()
{}

void StageManager::Init(CollisionManager* cm)
{
    // �n�ʁi�S�̃G���A�j
     stages.emplace_back(VGet(-250, 0, -250), VGet(250, 0, 250), GetColor(110, 110, 110), cm);

    // --- �����i�ݒu�G���A�j ---
    stages.emplace_back(VGet(-70, 0, 35), VGet(50, 1.5, 140), GetColor(130, 130, 130), cm); // �ݒu�ꏊ

    // --- ���� ---
    stages.emplace_back(VGet(-70, 40, -7), VGet(-72, 0, 140), GetColor(70, 70, 70), cm);     // ��
    
    // --- �E�� ---
    stages.emplace_back(VGet(50, 40, -7), VGet(52, 0, 140), GetColor(70, 70, 70), cm);      // ��

    // --- �� ---
    stages.emplace_back(VGet(-70, 1.5, 138), VGet(50, 20, 140), GetColor(130, 130, 130), cm);  // �����̕�
    stages.emplace_back(VGet(-70, 1.5, 115), VGet(-30, 20, 138), GetColor(130, 130, 130), cm);  // �����̕�
    stages.emplace_back(VGet(-70, 1.5, 113), VGet(-15, 35, 115), GetColor(130, 130, 130), cm);  // �����̕�
    stages.emplace_back(VGet(20, 1.5, 113), VGet(50, 21, 115), GetColor(130, 130, 130), cm);  // �����̕�
    stages.emplace_back(VGet(30, 21, 113), VGet(50, 35, 115), GetColor(130, 130, 130), cm);  // �����̕�
    stages.emplace_back(VGet(30, 1.5, 115), VGet(50, 20, 138), GetColor(130, 130, 130), cm);  // �����̕�
    stages.emplace_back(VGet(-70, 21, 113), VGet(50, 20, 140), GetColor(130, 130, 130), cm);  // �����̏�

    // --- �R���e�i���̎Օ��i�ݒu�ꏊ�����j ---
    stages.emplace_back(VGet(-10, 1.5, 58), VGet(3, 13.5, 71), GetColor(60, 60, 60), cm);  // ��
    stages.emplace_back(VGet(3, 1.5, 55), VGet(16, 13.5, 68), GetColor(60, 60, 60), cm);  // �E

    // --- �R���e�i���̎Օ��i���������j ---
    stages.emplace_back(VGet(-50, 1.5, 45), VGet(-35, 20.0, 90), GetColor(60, 60, 60), cm);
}

// �X�V
void StageManager::Update()
{
    for (auto& stage : stages) {
        stage.Update();
    }
}