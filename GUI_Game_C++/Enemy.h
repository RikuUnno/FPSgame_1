#pragma once
#include "DxLib.h"
#include "CapsuleCollider.h"

class Enemy : public CapsuleCollider 
{
private:
    unsigned int EnemyColor; // 自分の色

public:
    Enemy(VECTOR pos, double height, double radius, CollisionManager* manager); // コンストラクタ

    virtual ~Enemy(); // デストラクタ

    void Update(); // 更新

    void SetPosition();  // 位置更新用（下端から上端を計算）

    void SetRandomColor();

private:
    void Draw(); // 描画

    void OnCollisionEnter(Collider* other) override;
};