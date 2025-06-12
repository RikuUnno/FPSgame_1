#pragma once
#include <DxLib.h>

// �J�v�Z���^�R���C�_�[
class CapsuleCollider {
protected:
    VECTOR m_posTop;     // �J�v�Z���̏�[
    VECTOR m_posBottom;  // �J�v�Z���̉��[
    double m_height;     // �J�v�Z���̍���
    double m_radius;     // �J�v�Z���̔��a

    bool m_isHit;        // �Փ˂�����true

protected:
    CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius); // �R���X�g���N�^

    virtual ~CapsuleCollider(); // �f�X�g���N�^

public:
    VECTOR GetTop() const { return m_posTop; }       // m_posTop�̃Q�b�^�[
    VECTOR GetBottom() const { return m_posBottom; } // m_posBottom�̃Q�b�^�[
    double Getheight() const { return m_height; }    // m_height�̃Q�b�^�[
    double GetRadius() const { return m_radius; }    // m_radius�̃Q�b�^�[
    bool GetIsHit() { return m_isHit; }			  // m_isHit�̃Q�b�^�[

    bool SetIsHitTRUE() { return m_isHit = true; }   // m_isHit�̃Z�b�^�[�@true
    bool SetIsHitFALSE() { return m_isHit = false; } // m_isHit�̃Z�b�^�[  false
};