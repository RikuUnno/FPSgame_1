#pragma once
#include "Camera.h"

class GameManager
{
private:
	int m_sliderX = 50;      // �X���C�_�[���[��X���W
	int m_sliderY = 650;     // �X���C�_�[��Y���W
	int m_sliderWidth = 200; // �X���C�_�[�̕�
	bool m_isDragging = false; // �X���C�_�[���h���b�O�����ǂ���

private:
	Camera* m_cam;

public:
	GameManager(Camera* cam);
	virtual ~GameManager();

	GameManager(const GameManager& other) = delete;
	void operator=(const GameManager& other) = delete;

	void Update();

public:
	void DrawSensitivitySlider(); // ���x�X���C�_�[�̕`��
	void UpdateSensitivitySlider(); // ���x�X���C�_�[�̕`��
};
