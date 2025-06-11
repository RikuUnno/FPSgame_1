#pragma once
#include "CapsuleCollider.h"
#include <DxLib.h>

class Enemy : public CapsuleCollider {
private:
    VECTOR m_velocity; // ��ʂ̋��̒��S(���a�𑫂����������Ȃ��ƒn�ʂɖ��܂�)
    double m_height; // �G�̑傫���i�w�̍����j

public:
    Enemy(VECTOR pos, double height, double radius); // �R���X�g���N�^

    virtual ~Enemy(); // �f�X�g���N�^

    void Update(); // �X�V
    void Draw(); // �`��
};