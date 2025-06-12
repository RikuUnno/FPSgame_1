#pragma once

#include <DxLib.h>

class SphereCollider
{
protected:
	VECTOR m_spherePos; // ���̒��S�_
	double m_radius; // �~�̔��a

protected:
	SphereCollider(VECTOR spherePos, double redius); // �R���X�g���N�^
	virtual ~SphereCollider(); // �f�X�g���N�^

	bool HitCheckCollider();

public:
	VECTOR GetSpherePos() { return m_spherePos; } // m_spherePos�̃Q�b�^�[
	double GetSphereRadius() { return m_radius; } // m_radius�̃Q�b�^�[
};
