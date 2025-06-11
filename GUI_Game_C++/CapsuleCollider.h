#pragma once
#include <DxLib.h>

// カプセル型コライダー
class CapsuleCollider {
protected:
    VECTOR m_posTop;     // カプセルの上端
    VECTOR m_posBottom;  // カプセルの下端
    double m_radius;      // カプセルの半径

protected:
    CapsuleCollider(VECTOR top, VECTOR bottom, double radius); // コンストラクタ

    virtual ~CapsuleCollider(); // デストラクタ

public:
    VECTOR GetTop() const { return m_posTop; }       // m_posTopのゲッター
    VECTOR GetBottom() const { return m_posBottom; } // m_posBottomのゲッター
    double GetRadius() const { return m_radius; }     // m_radiusのゲッター
};