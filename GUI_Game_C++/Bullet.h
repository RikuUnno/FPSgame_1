#pragma once
#include "DxLib.h"
#include "SphereCollider.h"

class Bullet
	: public SphereCollider
{
private:
	VECTOR m_dir; // �i�s�����i���K���j
	double m_speed; // �ړ����x
	double m_life; // ����(�t���[����)
	unsigned int m_color; // �F

	CollisionManager* m_manager;

public:
	// �R���X�g���N�^
	Bullet(VECTOR pos, VECTOR dir, double radius, double speed, double life, CollisionManager* manager);

	// �f�X�g���N�^
	virtual ~Bullet();

	// �F�������_���ɐݒ肷��
	void SetRandomColor();

	// �X�V
	void Update();

	// �`��
	void DrawBullet() const; 

	// ��������
	bool IsAlive() const;
};