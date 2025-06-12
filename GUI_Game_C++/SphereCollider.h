#pragma once

#include <DxLib.h>

class SphereCollider
{
protected:
	VECTOR m_spherePos; // ���̒��S�_
	double m_radius;	// �~�̔��a
	bool m_isHit;       // �Փ˂�����true

protected:
	SphereCollider(VECTOR spherePos, double redius); // �R���X�g���N�^
	virtual ~SphereCollider(); // �f�X�g���N�^

public:
	VECTOR GetSpherePos() { return m_spherePos; } // m_spherePos�̃Q�b�^�[
	double GetSphereRadius() { return m_radius; } // m_radius�̃Q�b�^�[
	bool GetIsHit() { return m_isHit; }			  // m_isHit�̃Q�b�^�[

	bool SetIsHitTRUE() { return m_isHit = true; }   // m_isHit�̃Z�b�^�[�@true
	bool SetIsHitFALSE() { return m_isHit = false; } // m_isHit�̃Z�b�^�[  false
};
