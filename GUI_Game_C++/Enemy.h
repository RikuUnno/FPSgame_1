#pragma once
#include "CapsuleCollider.h"
#include <DxLib.h>

class Enemy : public CapsuleCollider {
private:
    VECTOR m_velocity; // 底面の球の中心(半径を足した数書かないと地面に埋まる)
    double m_height; // 敵の大きさ（背の高さ）

public:
    Enemy(VECTOR pos, double height, double radius); // コンストラクタ

    virtual ~Enemy(); // デストラクタ

    void Update(); // 更新
    void Draw(); // 描画
};