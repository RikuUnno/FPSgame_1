#pragma once
#include "Camera.h"

class GameManager
{
private:
    // ゲーム状態を表す列挙型
    enum class GameState
    {
        Ready,      // スタート前のカウントダウン待機状態
        Playing,    // ゲームプレイ中
        GameOver    // ゲームオーバー状態
    };

private:
    // 感度スライダー関連
    int m_sliderX;          // スライダー左端X座標
    int m_sliderY;         // スライダーY座標
    int m_sliderWidth;     // スライダー幅
    bool m_isDragging;   // スライダーつまみをドラッグ中かどうか

    // スコア・タイマー・ゲーム状態
    int m_score;             // 現在のスコア
    int m_highScore;         // 最高得点
    int m_timer;             // ゲームプレイ中の残り時間（フレーム数）
    int m_readyTimer;        // Ready状態のカウントダウンタイマー（フレーム数）
    GameState m_gameState; // ゲーム状態の管理

    int m_goDisplayTimer;       // GOの表示時間（フレーム）
    bool m_showHitText;     // HIT表示フラグ
    int m_hitTextTimer;         // HIT表示タイマー
    
    int m_gameOverDisplayTimer; // GAME OVER 表示時間

    int m_fontLarge = -1;        // 大きい文字描画用フォントハンドル
private:
    Camera* m_cam;

    // シングルトン用のコンストラクタをprivateに
    GameManager(Camera* cam);

public:
    ~GameManager();

    // コピーコンストラクタと代入演算子禁止
    GameManager(const GameManager& other) = delete;
    void operator=(const GameManager& other) = delete;

    // シングルトンのGetInstance
    static GameManager& GetInstance(Camera* cam = nullptr)
    {
        static GameManager instance(cam);
        return instance;
    }

    void Update();

    void AddScore(int value);       // 加点・減点
    void OnFire();                  // 弾発射時（－2点）
    void OnEnemyKilled();           // 敵撃破時（＋100点）

    int GetScore() const { return m_score; }
    int GetHighScore() const { return m_highScore; }
    bool IsGameStarted() const { return m_gameState == GameState::Playing; }

private:
    void DrawSensitivitySlider(); // 感度スライダーの描画
    void UpdateSensitivitySlider(); // 感度スライダーの描画

    void DrawHUD();
    void ResetGame();
    void FullResetGame();
};