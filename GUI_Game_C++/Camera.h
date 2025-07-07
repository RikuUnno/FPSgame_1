#pragma once
#include <vector>
#include "DxLib.h"
#include "Bullet.h"


// �J�����i�v���C���[�j�N���X
class Camera
{
private:
	VECTOR m_camPos; // �J�����̃|�W�V����
	VECTOR m_forward; // �L�����̑O�����ւ̃x�N�g���i�}�C�i�X�l�Ō������ɂȂ�j
	VECTOR m_right; // �L�����̉E�����ւ̃x�N�g��
	VECTOR m_front; // ���_�̌��Ă����(����)
	VECTOR m_target; // �J�����̌����^�[�Q�b�g
	double m_angleY; // ���E�̎��_�p�x(���[)
	double m_angleX; // �㉺�̎��_�p�x(�s�b�`)
	int m_mouseX, m_mouseY; // �}�E�X�̃|�C���g������XY
	int m_dx, m_dy; // ���_�̉�]
	const double M_SPEED = 0.2; // �ړ�����X�s�[�g(��t���[������)
	double m_sensitivity = 0.1; // �}�E�X�̃Z���V�i���x�j
	const double M_MAX_ANGLE = DX_PI / 2 - 0.1;

private:
	std::vector<Bullet> m_bulletList;
	int m_bulletTimer; // �����^�C�}�[
	const int m_INTERVAL = 20; // �^�C�}�[���g���������̃C���^�[�o��

private:
	CollisionManager* m_manager;

private:
	int m_sliderX = 50;      // �X���C�_�[���[��X���W
	int m_sliderY = 650;     // �X���C�_�[��Y���W
	int m_sliderWidth = 200; // �X���C�_�[�̕�
	bool m_isDragging = false; // �X���C�_�[���h���b�O�����ǂ���

public:
	// �R���X�g���N�^
	Camera(CollisionManager* manager);

	// �f�X�g���N�^
	virtual ~Camera();

	// �A�b�v�f�[�g���\�b�h�i��{�͂��̃��\�b�h�����s�֐��Ŏ��s����j�����͉�ʂ̒��S�n
	void Update(int centerX, int centerY);

public:
	void DrawSensitivitySlider(); // ���x�X���C�_�[�̕`��
	void UpdateSensitivitySlider(); // ���x�X���C�_�[�̕`��

private:

	// �v���C���[�̈ړ��͈�
	void ClampPositionInsideCircle(const VECTOR& center, double radius);

	//�@�L�[�{�[�h�̓��͏���
	void InputKey();

	// �}�E�X�̓���(��ʂ̃|�C���g��Ԃ�)
	void InputMouse();

	// �e�p��Update
	void BulletUpdate();

	// �e�̔���
	void InputFireKey();
};