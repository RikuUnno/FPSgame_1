#include "GameManager.h"
#include "GameInfo.h"
#include <algorithm>

// �R���X�g���N�^�F�J�����̃|�C���^���󂯎��A�t�H���g���쐬
GameManager::GameManager(Camera* cam)
    : m_cam(cam)
{
    // ���x�X���C�_�[�֘A
    m_sliderX = 50;          // �X���C�_�[���[X���W
    m_sliderY = 650;         // �X���C�_�[Y���W
    m_sliderWidth = 200;     // �X���C�_�[��
    m_isDragging = false;   // �X���C�_�[�܂݂��h���b�O�����ǂ���

    // �X�R�A�E�^�C�}�[�E�Q�[�����
    m_score = 0;             // ���݂̃X�R�A
    m_highScore = 0;         // �ō����_
    m_timer = 0;             // �Q�[���v���C���̎c�莞�ԁi�t���[�����j
    m_readyTimer = 0;        // Ready��Ԃ̃J�E���g�_�E���^�C�}�[�i�t���[�����j
    m_gameState = GameState::GameOver; // �Q�[����Ԃ̊Ǘ�

    m_goDisplayTimer = 0;       // GO�̕\�����ԁi�t���[���j
    m_showHitText = false;     // HIT�\���t���O
    m_hitTextTimer = 0;         // HIT�\���^�C�}�[

    m_gameOverDisplayTimer = 0; // GAME OVER �\������

    // �傫�������p�t�H���g���쐬
    m_fontLarge = CreateFontToHandle("�l�r �S�V�b�N", 48, 10, DX_FONTTYPE_ANTIALIASING);
}

// �f�X�g���N�^�F�쐬�����t�H���g��j��
GameManager::~GameManager()
{
    if (m_fontLarge != -1)
    {
        DeleteFontToHandle(m_fontLarge);
    }
}

// ���t���[���̍X�V����
void GameManager::Update()
{
    // H�L�[��R�L�[�Ńt�����Z�b�g�i�n�C�X�R�A�Ȃǂ��������j
    if (CheckHitKey(KEY_INPUT_H) && CheckHitKey(KEY_INPUT_R))
    {
        FullResetGame();
    }

    // H�L�[��S�L�[�𓯎�����������Q�[�������Z�b�g�iReady��Ԃɖ߂��j
    if (CheckHitKey(KEY_INPUT_H) && CheckHitKey(KEY_INPUT_S))
    {
        ResetGame();
    }

    // �Q�[����Ԃ��Ƃ̏���
    if (m_gameState == GameState::Ready)
    {
        if (m_readyTimer > 0)
        {
            m_readyTimer--;
        }
        else if (m_goDisplayTimer > 0)
        {
            m_goDisplayTimer--;
        }
        else
        {
            m_gameState = GameState::Playing;
            m_timer = 60 * 60;  // 60�b�^�C�}�[�Z�b�g
            m_score = 0;        // �X�R�A���Z�b�g
        }
    }
    else if (m_gameState == GameState::Playing)
    {
        m_timer--;

        // HIT�e�L�X�g�\���^�C�}�[�𖈃t���[�����炷
        if (m_hitTextTimer > 0)
        {
            m_hitTextTimer--;
            if (m_hitTextTimer <= 0)
            {
                m_showHitText = false;
            }
        }

        // �^�C���A�b�v
        if (m_timer <= 0)
        {
            m_gameOverDisplayTimer = 120;
            m_gameState = GameState::GameOver;
            if (m_score > m_highScore)
            {
                m_highScore = m_score;
            }
        }
    }
    else if (m_gameState == GameState::GameOver)
    {
        if (m_gameOverDisplayTimer > 0)
        {
            m_gameOverDisplayTimer--; // GAME OVER �\���̃J�E���g�_�E��
        }
    }

    // H�L�[�����Ă���Ԃ͊��x�X���C�_�[�̑��샂�[�h��
    if (CheckHitKey(KEY_INPUT_H))
    {
        SetMouseDispFlag(TRUE);      // �}�E�X�J�[�\���\��
        DrawSensitivitySlider();     // �X���C�_�[�̕`��
        UpdateSensitivitySlider();   // �X���C�_�[�̑��쏈��
    }
    else
    {
        SetMouseDispFlag(FALSE);     // �}�E�X�J�[�\����\��
    }

    // ��ʏ�ɃX�R�A��^�C�}�[�Ȃǂ�`��
    DrawHUD();
}

// �X�R�A�����Z�i�Q�[���v���C���̂ݗL���j
void GameManager::AddScore(int value)
{
    if (m_gameState == GameState::Playing)
    {
        m_score += value;
    }
}

// �e���ˎ��̌��_�����i2�_���_�j
void GameManager::OnFire()
{
    AddScore(-2);
}

// �G���j���̉��_�����i100�_���Z�j
void GameManager::OnEnemyKilled()
{
    AddScore(100);
    if (m_gameState == GameState::Playing) {
        m_showHitText = true;
        m_hitTextTimer = 15; // ��0.25�b�\��
    }
}

// ���x�X���C�_�[�̕`�揈��
void GameManager::DrawSensitivitySlider()
{
    // �X���C�_�[�̔w�i�o�[��`��
    DrawBox(m_sliderX, m_sliderY, m_sliderX + m_sliderWidth, m_sliderY + 10, GetColor(200, 200, 200), TRUE);

    // ���݂̊��x�ɉ������܂݂̈ʒu���v�Z���ĕ`��
    int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);
    DrawBox(knobX - 5, m_sliderY - 5, knobX + 5, m_sliderY + 15, GetColor(100, 100, 255), TRUE);

    // ���x�̐��l��\��
    DrawFormatString(m_sliderX, m_sliderY - 20, GetColor(255, 255, 255), "Sensitivity: %.4f", m_cam->GetSensitivity());
}

// ���x�X���C�_�[�̑���X�V�i�h���b�O�����j
void GameManager::UpdateSensitivitySlider()
{
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    // ���N���b�N����Ă����
    if (GetMouseInput() & MOUSE_INPUT_LEFT)
    {
        if (!m_isDragging)
        {
            // �܂݂̌��݂�X���W���v�Z
            int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);

            // �}�E�X���܂݂ɐG��Ă��邩����
            if (mouseX >= knobX - 10 && mouseX <= knobX + 10 &&
                mouseY >= m_sliderY - 10 && mouseY <= m_sliderY + 20)
            {
                m_isDragging = true;
            }
        }

        if (m_isDragging)
        {
            // �}�E�XX�ʒu���X���C�_�[�͈͂ɃN�����v�i0.0001�`0.1�j
            int newX = std::clamp(mouseX, m_sliderX, m_sliderX + m_sliderWidth);
            double newSensitivity = 0.0001 + ((double)(newX - m_sliderX) / m_sliderWidth) * (0.1 - 0.0001);
            m_cam->SetSensitivity(newSensitivity); // �J�����ɓK�p
        }
    }
    else
    {
        // �h���b�O�I��
        m_isDragging = false;
    }

}

// ��ʏ�ɃQ�[�����i�X�R�A�A�^�C�}�[�A��ԁj��`��
void GameManager::DrawHUD()
{
    if (m_gameState == GameState::Ready)
    {
        if (m_readyTimer > 0)
        {
            int x = WIN_SIZE_X / 2 - 100;
            int y = WIN_SIZE_Y / 2 - 24;
            DrawStringToHandle(x, y, "READY", GetColor(255, 255, 255), m_fontLarge);
            DrawFormatString(10, 10, GetColor(255, 255, 255), "Starting in: %d", m_readyTimer / 60 + 1);
        }
        else if (m_goDisplayTimer > 0)
        {
            int x = WIN_SIZE_X / 2 - 80;
            int y = WIN_SIZE_Y / 2 - 24;
            DrawStringToHandle(x, y, "GO!", GetColor(0, 255, 0), m_fontLarge);
        }
    }
    else if (m_gameState == GameState::Playing)
    {
        // �v���C���̓X�R�A�A�n�C�X�R�A�A�c�莞�Ԃ�\��
        DrawFormatString(10, 10, GetColor(255, 255, 255), "Score: %d", m_score);
        DrawFormatString(10, 30, GetColor(255, 255, 255), "HighScore: %d", m_highScore);
        DrawFormatString(10, 50, GetColor(255, 255, 255), "Time: %d", m_timer / 60);
        // �G�ɒe������������HIT
        if (m_showHitText)
        {
            int x = WIN_SIZE_X / 2 - 50;
            int y = WIN_SIZE_Y / 2 + 100;
            DrawStringToHandle(x, y, "HIT!", GetColor(255, 255, 0), m_fontLarge);
        }
    }
    else if (m_gameState == GameState::GameOver)
    {
        // �Q�[���I�[�o�[���̑傫�ȕ����\���ƍŏI�X�R�A�A�ăX�^�[�g�ē�
        int x = WIN_SIZE_X / 2 - 140;
        int y = WIN_SIZE_Y / 2 - 24;
        // GAME OVER ��2�b�Ԃ����\��
        if (m_gameState == GameState::GameOver && m_gameOverDisplayTimer > 0)
        {
            int x = WIN_SIZE_X / 2 - 140;
            int y = WIN_SIZE_Y / 2 - 24;
            DrawStringToHandle(x, y, "GAME OVER", GetColor(255, 0, 0), m_fontLarge);
        }
        DrawFormatString(10, 10, GetColor(255, 255, 255), "Score: %d", m_score);
        DrawFormatString(10, 30, GetColor(255, 255, 255), "HighScore: %d", m_highScore);
        DrawFormatString(10, 50, GetColor(255, 255, 255), "Press H+S to Restart");
        DrawFormatString(10, 70, GetColor(255, 255, 255), "Press H+R to FullReset");
    }
}

// �Q�[����Ready��Ԃɖ߂����Z�b�g����
void GameManager::ResetGame()
{
    m_readyTimer = 5 * 60;  // 5�b�Ԃ̃J�E���g�_�E��
    m_goDisplayTimer = 60;  // �uGO!�v�\��1�b
    m_gameState = GameState::Ready;
}

void GameManager::FullResetGame()
{
    m_score = 0;
    m_highScore = 0;
    m_timer = 0;
    m_readyTimer = 0;
    m_gameState = GameState::GameOver;
}
