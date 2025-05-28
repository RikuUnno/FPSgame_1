#include "GameInfo.h"

using namespace std;

// �J�����i�{�́j�̃N���X
class Camera
{
private:
	VECTOR m_camPos;
	double m_angleY;
	double m_angleX;
	int m_mouseX, m_mouseY; // �}�E�X�̃|�C���g������XY

public:
	Camera()
	{
		m_camPos = VGet(0.0f, 1.8f, -10.0f);

		m_angleY = 0.0;
		m_angleX = 0.0;

		m_mouseX = 0;
		m_mouseY = 0; 
	}

	virtual ~Camera(){}

	void Update(int centerX, int centerY)
	{
		InputMouse(); // �}�E�X�̌��݂̈ʒu���o��


	}

	void InputKey()
	{

	}

	void InputMouse()
	{
		GetMousePoint(&m_mouseX, &m_mouseY); // �}�E�X�̌��݂̈ʒu���o��

#ifdef _DEBUG
		DrawFormatString(0, 0, GetColor(255, 255, 255), // �f�o�b�N�p
			"�}�E�XX %d\n�}�E�XY %d", m_mouseX, m_mouseY); // �}�E�X�|�C���^�̈ʒu�𕶎���ŉ��K�Ɍ����悤�ɂ���
#endif _DEBUG
	}
};

// WinMain�֐�
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�C���h�E���[�h�ŋN��

	SetGraphMode(WIN_SIZE_X, WIN_SIZE_Y, 32); // ��ʃT�C�Y�̃Z�b�g

	SetWindowText("�Q�[�����hFPS�i���j"); // �E�B���h�E�̖��O�i���݂͉��j

	if (DxLib_Init() == -1) // DX���C�u�����̏�����
	{
		return -1; // �G���[���N�����璼���ɏI��
	}

	Camera cam; // �J�����{��

	const int centerX = WIN_SIZE_X / 2; // �}�E�X�̌Œ肷��ꏊ
	const int centerY = WIN_SIZE_Y / 2; // �}�E�X�̌Œ肷��ꏊ

	SetMousePoint(centerX, centerY); // �}�E�X�̏����l�̌Œ�
	SetMouseDispFlag(FALSE); // �}�E�X�̔�\��

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ESC�����������ʂ�������
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		clsDx();
		ClearDrawScreen();

		cam.Update();

		ScreenFlip();
	}

	DxLib_End(); // DX���C�u�����g�p�̏I������
}