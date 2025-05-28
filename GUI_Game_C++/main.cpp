#include "GameInfo.h"

using namespace std;

class Camera
{
	VECTOR pos = VGet(0.0f, 1.8f, -10.0f);

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

	int mouseX, mouseY; // �}�E�X�̃|�C���g������XY



	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ESC�����������ʂ�������
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		clsDx();
		ClearDrawScreen();

		GetMousePoint(&mouseX, &mouseY); // �}�E�X�̌��݂̈ʒu���o��

#ifdef _DEBUG
		DrawFormatString(0, 0, GetColor(255, 255, 255), // �f�o�b�N�p
			"�}�E�XX %d\n�}�E�XY %d", mouseX, mouseY); // �}�E�X�|�C���^�̈ʒu�𕶎���ŉ��K�Ɍ����悤�ɂ���
#endif _DEBUG

		ScreenFlip();
	}

	DxLib_End(); // DX���C�u�����g�p�̏I������
}