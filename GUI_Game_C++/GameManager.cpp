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
		// H�L�[�����Ă�ԁF�J�[�\���\�����X���C�_�[����
		SetMouseDispFlag(TRUE);

		DrawSensitivitySlider();
		UpdateSensitivitySlider();
		// �J���������}�E�X���_��]�͎~�߂�i�K�v�Ȃ�j
		return;
	}
	else
	{
		SetMouseDispFlag(FALSE);
	}
}

// ���x�X���C�_�[�̕`��
void GameManager::DrawSensitivitySlider() {
	// �X���C�_�[�̔w�i�o�[
	DrawBox(m_sliderX, m_sliderY, m_sliderX + m_sliderWidth, m_sliderY + 10, GetColor(200, 200, 200), TRUE);

	// �X���C�_�[�̂܂݂̈ʒu (���x��0.0001�`0.1�͈̔͂Ƃ����)
	int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);
	DrawBox(knobX - 5, m_sliderY - 5, knobX + 5, m_sliderY + 15, GetColor(100, 100, 255), TRUE);

	// ���x���\��
	DrawFormatString(m_sliderX, m_sliderY - 20, GetColor(255, 255, 255), "Sensitivity: %.4f", m_cam->GetSensitivity());
}

// ���x�X���C�_�[�̕`��
void GameManager::UpdateSensitivitySlider() {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		// �܂݂̃h���b�O�J�n����
		if (!m_isDragging) {
			int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);
			if (mouseX >= knobX - 10 && mouseX <= knobX + 10 &&
				mouseY >= m_sliderY - 10 && mouseY <= m_sliderY + 20) {
				m_isDragging = true;
			}
		}
		// �h���b�O���͊��x�X�V
		if (m_isDragging) {
			int newX = std::clamp(mouseX, m_sliderX, m_sliderX + m_sliderWidth);
			double newSensitivity = 0.0001 + ((double)(newX - m_sliderX) / m_sliderWidth) * (0.1 - 0.0001);
			m_cam->SetSensitivity(newSensitivity);
		}
	}
	else {
		// �}�E�X��������h���b�O�I��
		m_isDragging = false;
	}
}
