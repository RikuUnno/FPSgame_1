#pragma once
#include <DxLib.h>
#include "Collider.h"

class BoxCollider : public Collider
{
protected:
	BoxCollider(VECTOR min, VECTOR max, CollisionManager* manager); // �R���X�g���N�^
	virtual ~BoxCollider(); // �f�X�g���N�^

public:
	VECTOR GetBoxPosMin() { return std::get<BoxType>(data).min; } // m_spherePos�̃Q�b�^�[
	VECTOR GetBoxPosMax() { return std::get<BoxType>(data).max; } // m_radius�̃Q�b�^�[

	void SetAABB() override;
};