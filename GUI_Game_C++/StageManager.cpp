#include "StageManager.h"

StageManager::StageManager()
{
    stages.reserve(50); // ��������X�e�[�W�̃u���b�N���ɂ��
}

StageManager::~StageManager()
{}

void StageManager::Init(CollisionManager* cm)
{
    // �n�ʁi����߂̗����������O���[�j
    stages.emplace_back(
        VGet(-100, 0, -100), VGet(100, 1, 100),
        GetColor(110, 110, 110), cm
    );

    // ���̕ǁi�������薾��߂̊D�F�A�v���C���[��������Ȃ��j
    stages.emplace_back(
        VGet(-100, 1, 99), VGet(100, 20, 100),
        GetColor(160, 160, 160), cm
    );

    // ���̕ǁi���ԃO���[�F�^���������Ȃ��A�e�ɂȂ��ށj
    stages.emplace_back(
        VGet(-100, 1, -100), VGet(-98, 20, 100),
        GetColor(70, 70, 70), cm
    );

    // �E�̕ǁi���Ɠ����g�[���j
    stages.emplace_back(
        VGet(98, 1, -100), VGet(100, 20, 100),
        GetColor(70, 70, 70), cm
    );
}

// �X�V
void StageManager::Update()
{
    for (auto& stage : stages) {
        stage.Update();
    }
}