#include "GameManager.h"
#include "DxLib.h"
#include <algorithm>

GameManager::GameManager(Camera* cam)
	:m_cam(cam)
{}

GameManager::~GameManager()
{}

void GameManager::Update()
{
	if (CheckHitKey(KEY_INPUT_H))
	{
		// Hキー押してる間：カーソル表示＆スライダー操作
		SetMouseDispFlag(TRUE);

		DrawSensitivitySlider();
		UpdateSensitivitySlider();
		// カメラ操作やマウス視点回転は止める（必要なら）
		return;
	}
	else
	{
		SetMouseDispFlag(FALSE);
	}
}

// 感度スライダーの描画
void GameManager::DrawSensitivitySlider() {
	// スライダーの背景バー
	DrawBox(m_sliderX, m_sliderY, m_sliderX + m_sliderWidth, m_sliderY + 10, GetColor(200, 200, 200), TRUE);

	// スライダーのつまみの位置 (感度を0.0001～0.1の範囲とする例)
	int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);
	DrawBox(knobX - 5, m_sliderY - 5, knobX + 5, m_sliderY + 15, GetColor(100, 100, 255), TRUE);

	// ラベル表示
	DrawFormatString(m_sliderX, m_sliderY - 20, GetColor(255, 255, 255), "Sensitivity: %.4f", m_cam->GetSensitivity());
}

// 感度スライダーの描画
void GameManager::UpdateSensitivitySlider() {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		// つまみのドラッグ開始判定
		if (!m_isDragging) {
			int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);
			if (mouseX >= knobX - 10 && mouseX <= knobX + 10 &&
				mouseY >= m_sliderY - 10 && mouseY <= m_sliderY + 20) {
				m_isDragging = true;
			}
		}
		// ドラッグ中は感度更新
		if (m_isDragging) {
			int newX = std::clamp(mouseX, m_sliderX, m_sliderX + m_sliderWidth);
			double newSensitivity = 0.0001 + ((double)(newX - m_sliderX) / m_sliderWidth) * (0.1 - 0.0001);
			m_cam->SetSensitivity(newSensitivity);
		}
	}
	else {
		// マウス離したらドラッグ終了
		m_isDragging = false;
	}
}
