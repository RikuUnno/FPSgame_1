#include "Camera.h"

Camera::Camera()
{
	m_camPos = VGet(0.0, 10.0, -30.0); // カメラの初期化

	m_forward = VGet(0.0, 0.0, 0.0); // 前方向へのベクトルの初期化
	m_right = VGet(0.0, 0.0, 0.0); // 右方向へのベクトルの初期化

	m_front = VGet(0.0, 0.0, 0.0); // カメラの向く方向の初期化
	m_target = VGet(0.0, 0.0, 0.0); // カメラの向く位置の初期化

	m_angleY = 0.0;
	m_angleX = 0.0;

	m_mouseX = 0;
	m_mouseY = 0;

	m_dx = 0;
	m_dy = 0;

	m_bulletTimer = 0;
}

// デストラクタ
Camera::~Camera() {}

// アップデートメソッド（基本はこのメソッドを実行関数で実行する）引数は画面の中心地
void Camera::Update(int centerX, int centerY)
{
	InputFireKey();   // 弾発射チェック
	BulletUpdate();   // 弾の更新と描画

	InputMouse(); // マウスの入力
	InputKey(); //	キーの入力

	// 視点の回転（マウスの移動量で角度の変更）
	m_dx = m_mouseX - centerX;
	m_dy = m_mouseY - centerY;

	m_angleY += m_dx * M_SENSITIVITY; // 左右方向の視点の変更
	m_angleX -= m_dy * M_SENSITIVITY; // 上下方向の視点の変更

	if (m_angleX > M_MAX_ANGLE) m_angleX = M_MAX_ANGLE; // 下方向の制限
	if (m_angleX < -M_MAX_ANGLE) m_angleX = -M_MAX_ANGLE; // 上方向の制限

	SetMousePoint(centerX, centerY); // 視点の移動計算後にマウスポインタを中心に再設定

	// カメラの方向の設定
	m_front = VGet(
		(float)cos(m_angleX) * (float)sin(m_angleY),
		(float)sin(m_angleX),
		(float)cos(m_angleX) * (float)cos(m_angleY)
	);

	m_target = VAdd(m_camPos, m_front); // ターゲットの設定

	SetCameraNearFar(0.1f, 1000.0f); // 視錐台の調整
	SetCameraPositionAndTarget_UpVecY(m_camPos, m_target); // カメラのセット
}

//　キーボードの入力処理
void Camera::InputKey()
{
	// 前後左右の方向ベクトル計算
	m_forward = VGet((float)sin(m_angleY), 0, (float)cos(m_angleY));
	m_right = VGet((float)cos(m_angleY), 0, (float)-sin(m_angleY));

	// キーチェック
	if (CheckHitKey(KEY_INPUT_W)) { // 前
		m_camPos = VAdd(m_camPos, VScale(m_forward, (float)M_SPEED));
	}
	if (CheckHitKey(KEY_INPUT_S)) { // 後
		m_camPos = VSub(m_camPos, VScale(m_forward, (float)M_SPEED));
	}
	if (CheckHitKey(KEY_INPUT_A)) { // 左
		m_camPos = VSub(m_camPos, VScale(m_right, (float)M_SPEED));
	}
	if (CheckHitKey(KEY_INPUT_D)) { // 右
		m_camPos = VAdd(m_camPos, VScale(m_right, (float)M_SPEED));
	}
}

// マウスの入力(画面のポイントを返す)
void Camera::InputMouse()
{
	GetMousePoint(&m_mouseX, &m_mouseY); // マウスの現在の位置を出す

#ifdef _DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), // デバック用
		"マウスX %d\nマウスY %d", m_mouseX, m_mouseY); // マウスポインタの位置を文字列で快適に見れるようにした
#endif _DEBUG
}

// 弾用のUpdate
void Camera::BulletUpdate()
{
	m_bulletTimer++;
	if (m_bulletTimer >= 21)
	{
		m_bulletTimer = 0;
	}

	for (auto& bullet : m_bulletList)
	{
		bullet.Update(); // 弾の更新（前方への移動）
	}

	m_bulletList.erase(
		remove_if(m_bulletList.begin(), m_bulletList.end(), // 先頭から末尾までのイテレータ
			[](const Bullet& b) {return !b.IsAlive(); }), // 条件式（ラムダ式(コードの短縮化)）
		m_bulletList.end()
	);

	for (auto& bullet : m_bulletList)
	{
		bullet.DrawBullet(); // 描画
	}
}

// 弾の発射
void Camera::InputFireKey()
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT && m_bulletTimer >= m_INTERVAL)
	{
		m_bulletList.emplace_back(VAdd(m_camPos, VGet(0.0, -2.0, 0.0)), m_front, 1.0);
	}
}
