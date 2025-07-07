#pragma once
#include "DxLib.h"
#include "CapsuleCollider.h"

class Enemy : public CapsuleCollider 
{
private:
    unsigned int m_enemyColor; // 自分の色

    double m_minX; // 横移動の範囲(左)
    double m_maxX; // 横移動の範囲(右)
    double m_speed; // 移動速度
    bool m_movingRight; // 左移動の時用

    bool m_isDead;



public:
    Enemy(VECTOR pos, double height, double radius, double moveMinX, double moveMaxX, CollisionManager* manager); // コンストラクタ

    Enemy(const Enemy& other);

    virtual ~Enemy(); // デストラクタ

    void Update(); // 更新

    void SetPosition();  // 位置更新用（下端から上端を計算）

    void SetRandomColor();

    void Draw(); // 描画

public:
    bool IsDead() const { return m_isDead; } // 死んでいるか判定
    void Kill() { m_isDead = true; } // 死ぬときに押す

private:
    void OnCollisionEnter(Collider* other) override;

    void Move(); // 横移動
};