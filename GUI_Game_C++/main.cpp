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

// 初期化時などで一度呼ぶ(ライティング関係)
void SetupDefaultLight()
{
	// 方向ライトの有効化
	VECTOR lightDir = VNorm(VGet(.0f, -20.0f, 15.0f));
	SetLightDirection(lightDir);

	// 環境光
	SetLightAmbColor(GetColorF(0.7f, 0.7f, 0.7f, 1.0f));

	// ディフューズカラー
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

	SetUseLighting(TRUE);			// ライティングの有効
	SetUseZBuffer3D(TRUE);			// Zバッファ有効化
	SetWriteZBuffer3D(TRUE);		// Zバッファ書き込み
	SetLightEnable(TRUE);			 // ライティング全体を有効化
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

			VECTOR p1 = VGet((float)startX, -1.3f, (float)startZ);       // 左奥
			VECTOR p2 = VGet((float)startX + (float)cell, -1.3f, (float)startZ);       // 右奥
			VECTOR p3 = VGet((float)startX + (float)cell, -1.3f, (float)startZ + (float)cell);  // 右前
			VECTOR p4 = VGet((float)startX, -1.3f, (float)startZ + (float)cell);  // 左前

			int color = ((x + z) % 2 == 0) ? color1 : color2;

			DrawTriangle3D(p1, p2, p3, color, TRUE);
			DrawTriangle3D(p1, p3, p4, color, TRUE);
		}
	}

}

// クロスヘアの表示
void DrawCrossHair()
{
	const int centerX = WIN_SIZE_X / 2;
	const int centerY = WIN_SIZE_Y / 2;
	const int crossSize = 10;
	int crossColor = GetColor(255, 255, 255);

	DrawLine(centerX - crossSize, centerY, centerX + crossSize, centerY, crossColor); // 横
	DrawLine(centerX, centerY - crossSize, centerX, centerY + crossSize, crossColor); // 縦
}

// XYZのライン描画
void DrawVectorLine()
{
	DrawLine3D(VGet(0, 5, 0), VGet(100, 5, 0), GetColor(255, 0, 0));   // X軸
	DrawLine3D(VGet(0, 5, 0), VGet(0, 105, 0), GetColor(0, 255, 0));   // Y軸
	DrawLine3D(VGet(0, 5, 0), VGet(0, 5, 100), GetColor(0, 0, 255));   // Z軸
}

// WinMain関数
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウインドウモードで起動

	SetGraphMode(WIN_SIZE_X, WIN_SIZE_Y, 32); // 画面サイズのセット

	SetWindowText("FPSゲーム"); // ウィンドウの名前（現在は仮）

	if (DxLib_Init() == -1) // DXライブラリの初期化
	{
		return -1; // エラーが起きたら直ちに終了
	}

	SetupDefaultLight(); // ライティング設定

	CollisionManager cm; // 当たり判定関係
	 
	Camera cam(&cm); // カメラ本体

	EnemyManager em(&cm); // 敵

	StageManager sm; // ステージの生成

	const int centerX = WIN_SIZE_X / 2; // マウスの固定する場所
	const int centerY = WIN_SIZE_Y / 2; // マウスの固定する場所

	SetMousePoint(centerX, centerY); // マウスの初期値の固定
	SetMouseDispFlag(FALSE); // マウスの非表示

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	sm.Init(&cm); // ステージの生成
	em.InitSpawners();

	// ESCを押したら画面が落ちる
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		clsDx();
		ClearDrawScreen();

		sm.Update(); // ステージの更新

		DrawGround(); // グラウンドの描画

#ifdef _DEBUG
		DrawVectorLine(); // XYZのライン描画
#endif // _DEBUG

		em.Update(); // 敵の更新

		cam.Update(centerX, centerY); // カメラ(視点)の更新

		cm.HitCheck(); // 当たり判定

		DrawCrossHair(); // クロスヘアの描画（最前面）

		ScreenFlip();
	}

	DxLib_End(); // DXライブラリ使用の終了処理

	return 0;
}