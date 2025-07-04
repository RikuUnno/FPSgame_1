#pragma once
#include "DxLib.h"
#include "CapsuleCollider.h"

class Enemy : public CapsuleCollider 
{
private:
    unsigned int EnemyColor; // �����̐F

public:
    Enemy(VECTOR pos, double height, double radius, CollisionManager* manager); // �R���X�g���N�^

    virtual ~Enemy(); // �f�X�g���N�^

    void Update(); // �X�V

    void SetPosition();  // �ʒu�X�V�p�i���[�����[���v�Z�j

    void SetRandomColor();

private:
    void Draw(); // �`��

    void OnCollisionEnter(Collider* other) override;
};