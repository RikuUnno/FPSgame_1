#include "GameManager.h"
#include "GameInfo.h"
#include <algorithm>

// コンストラクタ：カメラのポインタを受け取り、フォントを作成
GameManager::GameManager(Camera* cam)
    : m_cam(cam)
{
    // 感度スライダー関連
    m_sliderX = 50;          // スライダー左端X座標
    m_sliderY = 650;         // スライダーY座標
    m_sliderWidth = 200;     // スライダー幅
    m_isDragging = false;   // スライダーつまみをドラッグ中かどうか

    // スコア・タイマー・ゲーム状態
    m_score = 0;             // 現在のスコア
    m_highScore = 0;         // 最高得点
    m_timer = 0;             // ゲームプレイ中の残り時間（フレーム数）
    m_readyTimer = 0;        // Ready状態のカウントダウンタイマー（フレーム数）
    m_gameState = GameState::GameOver; // ゲーム状態の管理

    m_goDisplayTimer = 0;       // GOの表示時間（フレーム）
    m_showHitText = false;     // HIT表示フラグ
    m_hitTextTimer = 0;         // HIT表示タイマー

    m_gameOverDisplayTimer = 0; // GAME OVER 表示時間

    // 大きい文字用フォントを作成
    m_fontLarge = CreateFontToHandle("ＭＳ ゴシック", 48, 10, DX_FONTTYPE_ANTIALIASING);
}

// デストラクタ：作成したフォントを破棄
GameManager::~GameManager()
{
    if (m_fontLarge != -1)
    {
        DeleteFontToHandle(m_fontLarge);
    }
}

// 毎フレームの更新処理
void GameManager::Update()
{
    // HキーとRキーでフルリセット（ハイスコアなども初期化）
    if (CheckHitKey(KEY_INPUT_H) && CheckHitKey(KEY_INPUT_R))
    {
        FullResetGame();
    }

    // HキーとSキーを同時押ししたらゲームをリセット（Ready状態に戻す）
    if (CheckHitKey(KEY_INPUT_H) && CheckHitKey(KEY_INPUT_S))
    {
        ResetGame();
    }

    // ゲーム状態ごとの処理
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
            m_timer = 60 * 60;  // 60秒タイマーセット
            m_score = 0;        // スコアリセット
        }
    }
    else if (m_gameState == GameState::Playing)
    {
        m_timer--;

        // HITテキスト表示タイマーを毎フレーム減らす
        if (m_hitTextTimer > 0)
        {
            m_hitTextTimer--;
            if (m_hitTextTimer <= 0)
            {
                m_showHitText = false;
            }
        }

        // タイムアップ
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
            m_gameOverDisplayTimer--; // GAME OVER 表示のカウントダウン
        }
    }

    // Hキー押している間は感度スライダーの操作モードへ
    if (CheckHitKey(KEY_INPUT_H))
    {
        SetMouseDispFlag(TRUE);      // マウスカーソル表示
        DrawSensitivitySlider();     // スライダーの描画
        UpdateSensitivitySlider();   // スライダーの操作処理
    }
    else
    {
        SetMouseDispFlag(FALSE);     // マウスカーソル非表示
    }

    // 画面上にスコアやタイマーなどを描画
    DrawHUD();
}

// スコア加減算（ゲームプレイ中のみ有効）
void GameManager::AddScore(int value)
{
    if (m_gameState == GameState::Playing)
    {
        m_score += value;
    }
}

// 弾発射時の減点処理（2点減点）
void GameManager::OnFire()
{
    AddScore(-2);
}

// 敵撃破時の加点処理（100点加算）
void GameManager::OnEnemyKilled()
{
    AddScore(100);
    if (m_gameState == GameState::Playing) {
        m_showHitText = true;
        m_hitTextTimer = 15; // 約0.25秒表示
    }
}

// 感度スライダーの描画処理
void GameManager::DrawSensitivitySlider()
{
    // スライダーの背景バーを描画
    DrawBox(m_sliderX, m_sliderY, m_sliderX + m_sliderWidth, m_sliderY + 10, GetColor(200, 200, 200), TRUE);

    // 現在の感度に応じたつまみの位置を計算して描画
    int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);
    DrawBox(knobX - 5, m_sliderY - 5, knobX + 5, m_sliderY + 15, GetColor(100, 100, 255), TRUE);

    // 感度の数値を表示
    DrawFormatString(m_sliderX, m_sliderY - 20, GetColor(255, 255, 255), "Sensitivity: %.4f", m_cam->GetSensitivity());
}

// 感度スライダーの操作更新（ドラッグ処理）
void GameManager::UpdateSensitivitySlider()
{
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    // 左クリックされている間
    if (GetMouseInput() & MOUSE_INPUT_LEFT)
    {
        if (!m_isDragging)
        {
            // つまみの現在のX座標を計算
            int knobX = m_sliderX + (int)((m_cam->GetSensitivity() - 0.0001) / (0.1 - 0.0001) * m_sliderWidth);

            // マウスがつまみに触れているか判定
            if (mouseX >= knobX - 10 && mouseX <= knobX + 10 &&
                mouseY >= m_sliderY - 10 && mouseY <= m_sliderY + 20)
            {
                m_isDragging = true;
            }
        }

        if (m_isDragging)
        {
            // マウスX位置をスライダー範囲にクランプ（0.0001～0.1）
            int newX = std::clamp(mouseX, m_sliderX, m_sliderX + m_sliderWidth);
            double newSensitivity = 0.0001 + ((double)(newX - m_sliderX) / m_sliderWidth) * (0.1 - 0.0001);
            m_cam->SetSensitivity(newSensitivity); // カメラに適用
        }
    }
    else
    {
        // ドラッグ終了
        m_isDragging = false;
    }

}

// 画面上にゲーム情報（スコア、タイマー、状態）を描画
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
        // プレイ中はスコア、ハイスコア、残り時間を表示
        DrawFormatString(10, 10, GetColor(255, 255, 255), "Score: %d", m_score);
        DrawFormatString(10, 30, GetColor(255, 255, 255), "HighScore: %d", m_highScore);
        DrawFormatString(10, 50, GetColor(255, 255, 255), "Time: %d", m_timer / 60);
        // 敵に弾が当たったらHIT
        if (m_showHitText)
        {
            int x = WIN_SIZE_X / 2 - 50;
            int y = WIN_SIZE_Y / 2 + 100;
            DrawStringToHandle(x, y, "HIT!", GetColor(255, 255, 0), m_fontLarge);
        }
    }
    else if (m_gameState == GameState::GameOver)
    {
        // ゲームオーバー時の大きな文字表示と最終スコア、再スタート案内
        int x = WIN_SIZE_X / 2 - 140;
        int y = WIN_SIZE_Y / 2 - 24;
        // GAME OVER を2秒間だけ表示
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

// ゲームをReady状態に戻すリセット処理
void GameManager::ResetGame()
{
    m_readyTimer = 5 * 60;  // 5秒間のカウントダウン
    m_goDisplayTimer = 60;  // 「GO!」表示1秒
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
