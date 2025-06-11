#pragma once
#include <DxLib.h>

// カプセル型コライダー
class CapsuleCollider {
protected:
    VECTOR m_posTop;     // カプセルの上端
    VECTOR m_posBottom;  // カプセルの下端
    double m_radius;      // カプセルの半径

public:
    CapsuleCollider(VECTOR top, VECTOR bottom, double radius); // コンストラクタ

    virtual ~CapsuleCollider(); // デストラクタ

    void SetCapsule(VECTOR top, VECTOR bottom, double radius); // 形状変化の更新用関数

    VECTOR GetTop() const { return m_posTop; }       // m_posTopのゲッター
    VECTOR GetBottom() const { return m_posBottom; } // m_posBottomのゲッター
    double GetRadius() const { return m_radius; }     // m_radiusのゲッター

    void SetPosition(VECTOR basePos, double height);  // 位置更新用（下端から上端を計算）
};