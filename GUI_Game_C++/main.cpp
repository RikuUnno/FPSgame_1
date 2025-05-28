#include "GameInfo.h"

using namespace std;

class Camera
{
	VECTOR pos = VGet(0.0f, 1.8f, -10.0f);

};

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

	int mouseX, mouseY; // マウスのポイントを入れるXY



	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ESCを押したら画面が落ちる
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		clsDx();
		ClearDrawScreen();

		GetMousePoint(&mouseX, &mouseY); // マウスの現在の位置を出す

#ifdef _DEBUG
		DrawFormatString(0, 0, GetColor(255, 255, 255), // デバック用
			"マウスX %d\nマウスY %d", mouseX, mouseY); // マウスポインタの位置を文字列で快適に見れるようにした
#endif _DEBUG

		ScreenFlip();
	}

	DxLib_End(); // DXライブラリ使用の終了処理
}