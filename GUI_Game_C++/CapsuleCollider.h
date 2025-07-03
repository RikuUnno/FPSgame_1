#pragma once
#include <DxLib.h>
#include "Collider.h"

// �J�v�Z���^�R���C�_�[
class CapsuleCollider
    : public Collider
{
protected:
    CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius, CollisionManager* manager); // �R���X�g���N�^

    virtual ~CapsuleCollider(); // �f�X�g���N�^

public:
    VECTOR GetTop() const { return std::get<CapsuleType>(data).m_posTop; }       // m_posTop�̃Q�b�^�[
    VECTOR GetBottom() const { return std::get<CapsuleType>(data).m_posBottom; } // m_posBottom�̃Q�b�^�[
    double Getheight() const { return std::get<CapsuleType>(data).m_height; }    // m_height�̃Q�b�^�[
    double GetRadius() const { return std::get<CapsuleType>(data).m_radius; }    // m_radius�̃Q�b�^�[

    void SetAABB() override; // AABB�̐ݒ�
};