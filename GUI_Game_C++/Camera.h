#pragma once
#include <vector>
#include "DxLib.h"
#include "Bullet.h"


// カメラ（プレイヤー）クラス
class Camera
{
private:
	VECTOR m_camPos; // カメラのポジション
	VECTOR m_forward; // キャラの前方向へのベクトル（マイナス値で後ろ方向になる）
	VECTOR m_right; // キャラの右方向へのベクトル
	VECTOR m_front; // 視点の見ている先(正面)
	VECTOR m_target; // カメラの向くターゲット
	double m_angleY; // 左右の視点角度(ヨー)
	double m_angleX; // 上下の視点角度(ピッチ)
	int m_mouseX, m_mouseY; // マウスのポイントを入れるXY
	int m_dx, m_dy; // 視点の回転
	const double M_SPEED = 0.2; // 移動するスピート(一フレームごと)
	double m_sensitivity = 0.1; // マウスのセンシ（感度）
	const double M_MAX_ANGLE = DX_PI / 2 - 0.1;

private:
	std::vector<Bullet> m_bulletList;
	int m_bulletTimer; // 生成タイマー
	const int m_INTERVAL = 20; // タイマーを使った生成のインターバル

private:
	CollisionManager* m_manager;
	
public:
	double GetSensitivity() const { return m_sensitivity; } // センシのゲッター
	void SetSensitivity(double value) { m_sensitivity = value; } // センシのセッター

public:
	// コンストラクタ
	Camera(CollisionManager* manager);

	// デストラクタ
	virtual ~Camera();

	// アップデートメソッド（基本はこのメソッドを実行関数で実行する）引数は画面の中心地
	void Update(int centerX, int centerY);

private:

	// プレイヤーの移動範囲
	void ClampPositionInsideCircle(const VECTOR& center, double radius);

	//　キーボードの入力処理
	void InputKey();

	// マウスの入力(画面のポイントを返す)
	void InputMouse();

	// 弾用のUpdate
	void BulletUpdate();

	// 弾の発射
	void InputFireKey();
};