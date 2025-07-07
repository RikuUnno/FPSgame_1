#include "Camera.h"
#include <algorithm>

Camera::Camera(CollisionManager* manager)
	: m_manager(manager)
{
	m_camPos = VGet(0.0, 10.0, -30.0); // �J�����̏�����

	m_forward = VGet(0.0, 0.0, 0.0); // �O�����ւ̃x�N�g���̏�����
	m_right = VGet(0.0, 0.0, 0.0); // �E�����ւ̃x�N�g���̏�����

	m_front = VGet(0.0, 0.0, 0.0); // �J�����̌��������̏�����
	m_target = VGet(0.0, 0.0, 0.0); // �J�����̌����ʒu�̏�����

	m_angleY = 0.0;
	m_angleX = 0.0;

	m_mouseX = 0;
	m_mouseY = 0;

	m_dx = 0;
	m_dy = 0;

	m_bulletTimer = 0;

	m_bulletList.reserve(200); // emplace_back�̃R�s�[��h������
}

// �f�X�g���N�^
Camera::~Camera() {}

// �A�b�v�f�[�g���\�b�h�i��{�͂��̃��\�b�h�����s�֐��Ŏ��s����j�����͉�ʂ̒��S�n
void Camera::Update(int centerX, int centerY)
{
	InputFireKey();   // �e���˃`�F�b�N
	BulletUpdate();   // �e�̍X�V�ƕ`��

	InputMouse(); // �}�E�X�̓���
	InputKey(); //	�L�[�̓���

	ClampPositionInsideCircle(VGet(0, 0, 0), 15.0); // �ړ��͈͂̐���

	// ���_�̉�]�i�}�E�X�̈ړ��ʂŊp�x�̕ύX�j
	m_dx = m_mouseX - centerX;
	m_dy = m_mouseY - centerY;

	m_angleY += m_dx * M_SENSITIVITY; // ���E�����̎��_�̕ύX
	m_angleX -= m_dy * M_SENSITIVITY; // �㉺�����̎��_�̕ύX

	if (m_angleX > M_MAX_ANGLE) m_angleX = M_MAX_ANGLE; // �������̐���
	if (m_angleX < -M_MAX_ANGLE) m_angleX = -M_MAX_ANGLE; // ������̐���

	SetMousePoint(centerX, centerY); // ���_�̈ړ��v�Z��Ƀ}�E�X�|�C���^�𒆐S�ɍĐݒ�

	// �J�����̕����̐ݒ�
	m_front = VGet(
		(float)cos(m_angleX) * (float)sin(m_angleY),
		(float)sin(m_angleX),
		(float)cos(m_angleX) * (float)cos(m_angleY)
	);

	m_target = VAdd(m_camPos, m_front); // �^�[�Q�b�g�̐ݒ�

	SetCameraNearFar(0.1f, 1000.0f); // ������̒���
	SetCameraPositionAndTarget_UpVecY(m_camPos, m_target); // �J�����̃Z�b�g

}

// �v���C���[�̈ړ��͈�
void Camera::ClampPositionInsideCircle(const VECTOR& center, double radius)
{
	// XZ���ʂ̃J�����ʒu�x�N�g���iY�͖����j
	double dx = m_camPos.x - center.x;
	double dz = m_camPos.z - center.z;

	double distSq = dx * dx + dz * dz;

	if (distSq > radius * radius)
	{
		double dist = sqrt(distSq);
		double clampedX = center.x + dx / dist * radius;
		double clampedZ = center.z + dz / dist * radius;

		// Y���W�͂��̂܂܈ێ�
		m_camPos.x = (float)clampedX;
		m_camPos.z = (float)clampedZ;
	}
}

//�@�L�[�{�[�h�̓��͏���
inline void Camera::InputKey()
{
	// �O�㍶�E�̕����x�N�g���v�Z
	m_forward = VGet((float)sin(m_angleY), 0, (float)cos(m_angleY));
	m_right = VGet((float)cos(m_angleY), 0, (float)-sin(m_angleY));

	// �L�[�`�F�b�N
	if (CheckHitKey(KEY_INPUT_W)) { // �O
		m_camPos = VAdd(m_camPos, VScale(m_forward, (float)M_SPEED));
	}
	if (CheckHitKey(KEY_INPUT_S)) { // ��
		m_camPos = VSub(m_camPos, VScale(m_forward, (float)M_SPEED));
	}
	if (CheckHitKey(KEY_INPUT_A)) { // ��
		m_camPos = VSub(m_camPos, VScale(m_right, (float)M_SPEED));
	}
	if (CheckHitKey(KEY_INPUT_D)) { // �E
		m_camPos = VAdd(m_camPos, VScale(m_right, (float)M_SPEED));
	}
}

// �}�E�X�̓���(��ʂ̃|�C���g��Ԃ�)
void Camera::InputMouse()
{
	GetMousePoint(&m_mouseX, &m_mouseY); // �}�E�X�̌��݂̈ʒu���o��

#ifdef _DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), // �f�o�b�N�p
		"�}�E�XX %d\n�}�E�XY %d", m_mouseX, m_mouseY); // �}�E�X�|�C���^�̈ʒu�𕶎���ŉ��K�Ɍ����悤�ɂ���
#endif _DEBUG
}

// �e�p��Update
void Camera::BulletUpdate()
{
	m_bulletTimer--;

#ifdef _DEBUG
	DrawFormatString(0, 45, GetColor(255, 255, 255), // �f�o�b�N�p
		"m_bulletTimer:%d", m_bulletTimer); // �}�E�X�|�C���^�̈ʒu�𕶎���ŉ��K�Ɍ����悤�ɂ���
#endif _DEBUG

	if (m_bulletTimer < -10) m_bulletTimer = 0;

	for (auto& bullet : m_bulletList)
	{
		bullet.Update(); // �e�̍X�V�i�O���ւ̈ړ��j
	}

	std::erase_if(m_bulletList, [](const Bullet& b) {
		return !b.IsAlive() || b.GetIsHit();
		});

	for (auto& bullet : m_bulletList)
	{
		bullet.DrawBullet(); // �`��
	}
}

// �e�̔���
void Camera::InputFireKey()
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT && m_bulletTimer <= 0)
	{
		VECTOR spawnPos = VAdd(m_camPos, VScale(m_front, 2.0f)); // ���ʂɃI�t�Z�b�g
		m_bulletList.emplace_back(spawnPos, m_front, 0.5, 5, 120.0, m_manager);
		m_bulletTimer = m_INTERVAL;
	}
}
