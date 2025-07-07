#pragma once
#include "DxLib.h"
#include "CapsuleCollider.h"

class Enemy : public CapsuleCollider 
{
private:
    unsigned int m_enemyColor; // �����̐F

    double m_minX; // ���ړ��͈̔�(��)
    double m_maxX; // ���ړ��͈̔�(�E)
    double m_speed; // �ړ����x
    bool m_movingRight; // ���ړ��̎��p

    bool m_isDead;



public:
    Enemy(VECTOR pos, double height, double radius, double moveMinX, double moveMaxX, CollisionManager* manager); // �R���X�g���N�^

    Enemy(const Enemy& other);

    virtual ~Enemy(); // �f�X�g���N�^

    void Update(); // �X�V

    void SetPosition();  // �ʒu�X�V�p�i���[�����[���v�Z�j

    void SetRandomColor();

    void Draw(); // �`��

public:
    bool IsDead() const { return m_isDead; } // ����ł��邩����
    void Kill() { m_isDead = true; } // ���ʂƂ��ɉ���

private:
    void OnCollisionEnter(Collider* other) override;

    void Move(); // ���ړ�
};