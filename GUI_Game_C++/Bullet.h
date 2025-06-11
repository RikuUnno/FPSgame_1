#pragma once
#include "DxLib.h"

class Bullet
{
private:
	VECTOR m_pos; // ���݂̈ʒu
	VECTOR m_dir; // �i�s�����i���K���j
	double m_speed; // �ړ����x
	double m_life; // ����(�t���[����)

public:
	// �R���X�g���N�^
	Bullet(VECTOR pos, VECTOR dir, double speed = 1.0, double life = 300.0);

	// �f�X�g���N�^
	virtual ~Bullet();

	// �X�V
	void Update();

	// �`��
	void DrawBullet() const; 

	// ��������
	bool IsAlive() const;
};