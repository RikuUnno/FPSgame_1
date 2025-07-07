#include "GameInfo.h"
#include "Camera.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "StageManager.h"

#include <cmath>
#include <vector>
using namespace std;

// ���������Ȃǂň�x�Ă�(���C�e�B���O�֌W)
void SetupDefaultLight()
{
	// �������C�g�̗L����
	VECTOR lightDir = VNorm(VGet(.0f, -20.0f, 15.0f));
	SetLightDirection(lightDir);

	// ����
	SetLightAmbColor(GetColorF(0.7f, 0.7f, 0.7f, 1.0f));

	// �f�B�t���[�Y�J���[
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

	SetUseLighting(TRUE);			// ���C�e�B���O�̗L��
	SetUseZBuffer3D(TRUE);			// Z�o�b�t�@�L����
	SetWriteZBuffer3D(TRUE);		// Z�o�b�t�@��������
	SetLightEnable(TRUE);			 // ���C�e�B���O�S�̂�L����
}

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

			VECTOR p1 = VGet((float)startX, -1.3f, (float)startZ);       // ����
			VECTOR p2 = VGet((float)startX + (float)cell, -1.3f, (float)startZ);       // �E��
			VECTOR p3 = VGet((float)startX + (float)cell, -1.3f, (float)startZ + (float)cell);  // �E�O
			VECTOR p4 = VGet((float)startX, -1.3f, (float)startZ + (float)cell);  // ���O

			int color = ((x + z) % 2 == 0) ? color1 : color2;

			DrawTriangle3D(p1, p2, p3, color, TRUE);
			DrawTriangle3D(p1, p3, p4, color, TRUE);
		}
	}

}

// �N���X�w�A�̕\��
void DrawCrossHair()
{
	const int centerX = WIN_SIZE_X / 2;
	const int centerY = WIN_SIZE_Y / 2;
	const int crossSize = 10;
	int crossColor = GetColor(255, 255, 255);

	DrawLine(centerX - crossSize, centerY, centerX + crossSize, centerY, crossColor); // ��
	DrawLine(centerX, centerY - crossSize, centerX, centerY + crossSize, crossColor); // �c
}

// XYZ�̃��C���`��
void DrawVectorLine()
{
	DrawLine3D(VGet(0, 5, 0), VGet(100, 5, 0), GetColor(255, 0, 0));   // X��
	DrawLine3D(VGet(0, 5, 0), VGet(0, 105, 0), GetColor(0, 255, 0));   // Y��
	DrawLine3D(VGet(0, 5, 0), VGet(0, 5, 100), GetColor(0, 0, 255));   // Z��
}

// WinMain�֐�
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�C���h�E���[�h�ŋN��

	SetGraphMode(WIN_SIZE_X, WIN_SIZE_Y, 32); // ��ʃT�C�Y�̃Z�b�g

	SetWindowText("FPS�Q�[��"); // �E�B���h�E�̖��O�i���݂͉��j

	if (DxLib_Init() == -1) // DX���C�u�����̏�����
	{
		return -1; // �G���[���N�����璼���ɏI��
	}

	SetupDefaultLight(); // ���C�e�B���O�ݒ�

	CollisionManager cm; // �����蔻��֌W
	 
	Camera cam(&cm); // �J�����{��

	EnemyManager em(&cm); // �G

	StageManager sm; // �X�e�[�W�̐���

	const int centerX = WIN_SIZE_X / 2; // �}�E�X�̌Œ肷��ꏊ
	const int centerY = WIN_SIZE_Y / 2; // �}�E�X�̌Œ肷��ꏊ

	SetMousePoint(centerX, centerY); // �}�E�X�̏����l�̌Œ�
	SetMouseDispFlag(FALSE); // �}�E�X�̔�\��

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	sm.Init(&cm); // �X�e�[�W�̐���
	em.InitSpawners();

	// ESC�����������ʂ�������
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		clsDx();
		ClearDrawScreen();

		sm.Update(); // �X�e�[�W�̍X�V

		DrawGround(); // �O���E���h�̕`��

#ifdef _DEBUG
		DrawVectorLine(); // XYZ�̃��C���`��
#endif // _DEBUG

		em.Update(); // �G�̍X�V

		cam.Update(centerX, centerY); // �J����(���_)�̍X�V

		cm.HitCheck(); // �����蔻��

		DrawCrossHair(); // �N���X�w�A�̕`��i�őO�ʁj

		ScreenFlip();
	}

	DxLib_End(); // DX���C�u�����g�p�̏I������

	return 0;
}