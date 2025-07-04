#pragma once
#include "DxLib.h"
#include <vector>
#include <variant>

class CollisionManager; // �O���錾

enum class ColliderType // Collider�̕���
{
    Box,
    Sphere,
    Capsule
};

struct BoxType {               // AABB��Box
    VECTOR min; // �ŏ����W
    VECTOR max; // �ő���W
}typedef AABB;

struct SphereType           // ��    
{
    VECTOR m_spherePos; // ���̒��S�_
    double m_radius;	// �~�̔��a
};

struct CapsuleType          // �J�v�Z��
{
    VECTOR m_posTop;     // �J�v�Z���̏�[
    VECTOR m_posBottom;  // �J�v�Z���̉��[
    double m_height;     // �J�v�Z���̍���
    double m_radius;     // �J�v�Z���̔��a
};

class Collider
{
protected:
    bool m_isHit;       // �Փ˂�����true
    AABB aabb;

    ColliderType type;

    std::variant<BoxType, SphereType, CapsuleType> data;

    CollisionManager* m_manager;

protected:
    std::vector<Collider*>previousHitColliders; //�O�i�������̃t���[���j�̓�������Collider
    std::vector<Collider*>currentHitColliders;  //����(�������̃t���[��)�̓�������Collider

public:
    // �R���X�g���N�^
    Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, CollisionManager* manager);

    // �f�X�g���N�^
    virtual ~Collider();

    // m_isHit�̃Z�b�^�[�@true
    void SetIsHitTRUE();
    // m_isHit�̃Z�b�^�[�@false
    void SetIsHitFALSE();

    virtual void SetAABB() = 0; // �e�R���C�_�[�Ɏ������e��`��

    AABB GetAABB() const { return aabb; }// AABB�̃Q�b�^�[
    ColliderType GetType() const { return type; }// �\���̂�Type��Ԃ�
    bool GetIsHit() const { return m_isHit; } // m_isHit�̃Q�b�^�[

    const BoxType* GetBox() const { return std::get_if<BoxType>(&data); } // BoxType�̃Q�b�^�[
    const SphereType* GetSphere() const { return std::get_if<SphereType>(&data); } // SphereType�̃Q�b�^�[
    const CapsuleType* GetCapsule() const { return std::get_if<CapsuleType>(&data); } // CapsuleType�̃Q�b�^�[

    void AddCurrentHitCollider(Collider* col);

    void DrawAABB() const;

public:
    void CheckCollisionEvent(); // �Փ˔���̃C�x���g���Ηp

protected:
    virtual void OnCollisionEnter(Collider* other) {}   // �ڐG����
    virtual void OnCollisionStay(Collider* other) {}    // �ڐG��
    virtual void OnCollisionExit(Collider* other) {}    // �ڐG��
};
 