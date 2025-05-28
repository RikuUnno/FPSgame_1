#include "GameInfo.h"

using namespace std;

// カメラ（本体）のクラス
class Camera
{
private:
	VECTOR m_camPos;
	double m_angleY;
	double m_angleX;
	int m_mouseX, m_mouseY; // マウスのポイントを入れるXY

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
		InputMouse(); // マウスの現在の位置を出す


	}

	void InputKey()
	{

	}

	void InputMouse()
	{
		GetMousePoint(&m_mouseX, &m_mouseY); // マウスの現在の位置を出す

#ifdef _DEBUG
		DrawFormatString(0, 0, GetColor(255, 255, 255), // デバック用
			"マウスX %d\nマウスY %d", m_mouseX, m_mouseY); // マウスポインタの位置を文字列で快適に見れるようにした
#endif _DEBUG
	}
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

	Camera cam; // カメラ本体

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

		cam.Update();

		ScreenFlip();
	}

	DxLib_End(); // DXライブラリ使用の終了処理
}