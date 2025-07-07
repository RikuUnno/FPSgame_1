#pragma once
#include "Camera.h"

class GameManager
{
private:
    // �Q�[����Ԃ�\���񋓌^
    enum class GameState
    {
        Ready,      // �X�^�[�g�O�̃J�E���g�_�E���ҋ@���
        Playing,    // �Q�[���v���C��
        GameOver    // �Q�[���I�[�o�[���
    };

private:
    // ���x�X���C�_�[�֘A
    int m_sliderX;          // �X���C�_�[���[X���W
    int m_sliderY;         // �X���C�_�[Y���W
    int m_sliderWidth;     // �X���C�_�[��
    bool m_isDragging;   // �X���C�_�[�܂݂��h���b�O�����ǂ���

    // �X�R�A�E�^�C�}�[�E�Q�[�����
    int m_score;             // ���݂̃X�R�A
    int m_highScore;         // �ō����_
    int m_timer;             // �Q�[���v���C���̎c�莞�ԁi�t���[�����j
    int m_readyTimer;        // Ready��Ԃ̃J�E���g�_�E���^�C�}�[�i�t���[�����j
    GameState m_gameState; // �Q�[����Ԃ̊Ǘ�

    int m_goDisplayTimer;       // GO�̕\�����ԁi�t���[���j
    bool m_showHitText;     // HIT�\���t���O
    int m_hitTextTimer;         // HIT�\���^�C�}�[
    
    int m_gameOverDisplayTimer; // GAME OVER �\������

    int m_fontLarge = -1;        // �傫�������`��p�t�H���g�n���h��
private:
    Camera* m_cam;

    // �V���O���g���p�̃R���X�g���N�^��private��
    GameManager(Camera* cam);

public:
    ~GameManager();

    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q�֎~
    GameManager(const GameManager& other) = delete;
    void operator=(const GameManager& other) = delete;

    // �V���O���g����GetInstance
    static GameManager& GetInstance(Camera* cam = nullptr)
    {
        static GameManager instance(cam);
        return instance;
    }

    void Update();

    void AddScore(int value);       // ���_�E���_
    void OnFire();                  // �e���ˎ��i�|2�_�j
    void OnEnemyKilled();           // �G���j���i�{100�_�j

    int GetScore() const { return m_score; }
    int GetHighScore() const { return m_highScore; }
    bool IsGameStarted() const { return m_gameState == GameState::Playing; }

private:
    void DrawSensitivitySlider(); // ���x�X���C�_�[�̕`��
    void UpdateSensitivitySlider(); // ���x�X���C�_�[�̕`��

    void DrawHUD();
    void ResetGame();
    void FullResetGame();
};