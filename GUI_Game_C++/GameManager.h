#pragma once
#include "Camera.h"

class GameManager
{
private:
	int m_sliderX = 50;      // スライダー左端のX座標
	int m_sliderY = 650;     // スライダーのY座標
	int m_sliderWidth = 200; // スライダーの幅
	bool m_isDragging = false; // スライダーをドラッグ中かどうか

private:
	Camera* m_cam;

public:
	GameManager(Camera* cam);
	virtual ~GameManager();

	GameManager(const GameManager& other) = delete;
	void operator=(const GameManager& other) = delete;

	void Update();

public:
	void DrawSensitivitySlider(); // 感度スライダーの描画
	void UpdateSensitivitySlider(); // 感度スライダーの描画
};
