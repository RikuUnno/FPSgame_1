#pragma once
#include <DxLib.h>
#include "Collider.h"

class SphereCollider : public Collider
{
protected:
	SphereCollider(VECTOR spherePos, double redius, CollisionManager* manager); // �R���X�g���N�^
	virtual ~SphereCollider(); // �f�X�g���N�^

public:
	VECTOR GetSpherePos() { return std::get<SphereType>(data).m_spherePos; } // m_spherePos�̃Q�b�^�[
	double GetSphereRadius() { return std::get<SphereType>(data).m_radius; } // m_radius�̃Q�b�^�[
	bool GetIsHit() { return m_isHit; }			  // m_isHit�̃Q�b�^�[

	void SetAABB() override;
};
