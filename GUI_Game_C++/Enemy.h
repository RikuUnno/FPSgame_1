#pragma once
#include "CapsuleCollider.h"
#include <DxLib.h>

class Enemy : public CapsuleCollider 
{
public:
    Enemy(VECTOR pos, double height, double radius); // コンストラクタ

    virtual ~Enemy(); // デストラクタ

    void Update(); // 更新

    void SetPosition();  // 位置更新用（下端から上端を計算）

private:
    void Draw(); // 描画
};