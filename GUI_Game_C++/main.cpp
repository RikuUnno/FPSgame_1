#include "GameInfo.h"
#include "Camera.h"
#include "Enemy.h"
#include "CapsuleCollider.h"

#include <cmath>
#include <vector>

using namespace std;

// 初期化時などで一度呼ぶ
void SetupDefaultLight() 
{
	SetUseLighting(TRUE);

	VECTOR dir = VNorm(VGet(0.0f, -1.0f, -1.0f));
	SetLightDirection(dir);

	SetUseZBuffer3D(TRUE);         // Zバッファ有効化
	SetWriteZBuffer3D(TRUE);       // Zバッファ書き込み
	SetLightEnable(TRUE);		   // ライティング全体を有効化
}

// グラウンドの表示
void DrawGround()
{
	const int num = 10;         // マスの数（10×10）
	const double size = 500.0;  // 全体のサイズ
	const double cell = size / num; // 1マスronの大きさ（50.0）

	int color1 = GetColor(180, 180, 180); // 明るいグレー
	int color2 = GetColor(120, 120, 120); // 暗いグレー

	for (int z = 0; z < num; ++z)
	{
		for (int x = 0; x < num; ++x)
		{
			// 左下の座標を計算（中心を原点にする）
			double startX = -size / 2 + x * cell;
			double startZ = -size / 2 + z * cell;

			VECTOR p1 = VGet((float)startX, 0.0f, (float)startZ);       // 左奥
			VECTOR p2 = VGet((float)startX + (float)cell, 0.0f, (float)startZ);       // 右奥
			VECTOR p3 = VGet((float)startX + (float)cell, 0.0f, (float)startZ + (float)cell);  // 右前
			VECTOR p4 = VGet((float)startX, 0.0f, (float)startZ + (float)cell);  // 左前

			int color = ((x + z) % 2 == 0) ? color1 : color2;

			DrawTriangle3D(p1, p2, p3, color, TRUE);
			DrawTriangle3D(p1, p3, p4, color, TRUE);
		}
	}

}

// WinMain関数
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウインドウモードで起動

	SetGraphMode(WIN_SIZE_X, WIN_SIZE_Y, 32); // 画面サイズのセット

	SetWindowText("ゲーム合宿FPS（仮）"); // ウィンドウの名前（現在は仮）



	if (DxLib_Init() == -1) // DXライブラリの初期化
	{
		return -1; // エラーが起きたら直ちに終了
	}

	SetupDefaultLight();

	Camera cam; // カメラ本体

	Enemy enemy(VGet(0.0, 0.0, 0.0), 10, 2);

	const int centerX = WIN_SIZE_X / 2; // マウスの固定する場所
	const int centerY = WIN_SIZE_Y / 2; // マウスの固定する場所

	SetMousePoint(centerX, centerY); // マウスの初期値の固定
	SetMouseDispFlag(FALSE); // マウスの非表示

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ESCを押したら画面が落ちる
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		clsDx();
		ClearDrawScreen();

		DrawGround(); // グラウンドの描画

#ifdef _DEBUG
		DrawLine3D(VGet(0, 5, 0), VGet(100, 5, 0), GetColor(255, 0, 0));   // X軸
		DrawLine3D(VGet(0, 5, 0), VGet(0, 105, 0), GetColor(0, 255, 0));   // Y軸
		DrawLine3D(VGet(0, 5, 0), VGet(0, 5, 100), GetColor(0, 0, 255));   // Z軸
#endif // _DEBUG

		cam.Update(centerX, centerY);

		enemy.Update();
		

		ScreenFlip();
	}

	DxLib_End(); // DXライブラリ使用の終了処理
}