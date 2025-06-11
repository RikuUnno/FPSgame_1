#pragma once
#include "CapsuleCollider.h"
#include <DxLib.h>

class Enemy : public CapsuleCollider 
{
public:
    Enemy(VECTOR pos, double height, double radius); // �R���X�g���N�^

    virtual ~Enemy(); // �f�X�g���N�^

    void Update(); // �X�V

    void SetPosition();  // �ʒu�X�V�p�i���[�����[���v�Z�j

private:
    void Draw(); // �`��
};