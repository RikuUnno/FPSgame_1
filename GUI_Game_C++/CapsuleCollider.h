#pragma once
#include <DxLib.h>

// �J�v�Z���^�R���C�_�[
class CapsuleCollider {
protected:
    VECTOR m_posTop;     // �J�v�Z���̏�[
    VECTOR m_posBottom;  // �J�v�Z���̉��[
    double m_radius;      // �J�v�Z���̔��a

public:
    CapsuleCollider(VECTOR top, VECTOR bottom, double radius); // �R���X�g���N�^

    virtual ~CapsuleCollider(); // �f�X�g���N�^

    void SetCapsule(VECTOR top, VECTOR bottom, double radius); // �`��ω��̍X�V�p�֐�

    VECTOR GetTop() const { return m_posTop; }       // m_posTop�̃Q�b�^�[
    VECTOR GetBottom() const { return m_posBottom; } // m_posBottom�̃Q�b�^�[
    double GetRadius() const { return m_radius; }     // m_radius�̃Q�b�^�[

    void SetPosition(VECTOR basePos, double height);  // �ʒu�X�V�p�i���[�����[���v�Z�j
};