#include "GameInfo.h"
#include "Camera.h"
#include "Enemy.h"
#include "CapsuleCollider.h"

#include <cmath>
#include <vector>

using namespace std;


// �O���E���h�̕\��
void DrawGround()
{
	const int num = 10;         // �}�X�̐��i10�~10�j
	const double size = 500.0;  // �S�̂̃T�C�Y
	const double cell = size / num; // 1�}�Xron�̑傫���i50.0�j

	int color1 = GetColor(180, 180, 180); // ���邢�O���[
	int color2 = GetColor(120, 120, 120); // �Â��O���[

	for (int z = 0; z < num; ++z)
	{
		for (int x = 0; x < num; ++x)
		{
			// �����̍��W���v�Z�i���S�����_�ɂ���j
			double startX = -size / 2 + x * cell;
			double startZ = -size / 2 + z * cell;

			VECTOR p1 = VGet(startX, 0.0f, startZ);       // ����
			VECTOR p2 = VGet(startX + cell, 0.0f, startZ);       // �E��
			VECTOR p3 = VGet(startX + cell, 0.0f, startZ + cell);  // �E�O
			VECTOR p4 = VGet(startX, 0.0f, startZ + cell);  // ���O

			int color = ((x + z) % 2 == 0) ? color1 : color2;

			DrawTriangle3D(p1, p2, p3, color, TRUE);
			DrawTriangle3D(p1, p3, p4, color, TRUE);
		}
	}

}

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

	Enemy enemy(VGet(0.0, 0.0, 0.0), 10, 2);

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

		DrawGround(); // �O���E���h�̕`��

#ifdef _DEBUG
		DrawLine3D(VGet(0, 5, 0), VGet(100, 5, 0), GetColor(255, 0, 0));   // X��
		DrawLine3D(VGet(0, 5, 0), VGet(0, 105, 0), GetColor(0, 255, 0));   // Y��
		DrawLine3D(VGet(0, 5, 0), VGet(0, 5, 100), GetColor(0, 0, 255));   // Z��
#endif // _DEBUG

		cam.Update(centerX, centerY);

		enemy.Update();
		

		ScreenFlip();
	}

	DxLib_End(); // DX���C�u�����g�p�̏I������
}