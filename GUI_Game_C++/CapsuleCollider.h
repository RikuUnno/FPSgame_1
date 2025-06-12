#pragma once
#include <DxLib.h>

// カプセル型コライダー
class CapsuleCollider {
protected:
    VECTOR m_posTop;     // カプセルの上端
    VECTOR m_posBottom;  // カプセルの下端
    double m_height;     // カプセルの高さ
    double m_radius;     // カプセルの半径

    bool m_isHit;        // 衝突したらtrue

protected:
    CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius); // コンストラクタ

    virtual ~CapsuleCollider(); // デストラクタ

public:
    VECTOR GetTop() const { return m_posTop; }       // m_posTopのゲッター
    VECTOR GetBottom() const { return m_posBottom; } // m_posBottomのゲッター
    double Getheight() const { return m_height; }    // m_heightのゲッター
    double GetRadius() const { return m_radius; }    // m_radiusのゲッター
    bool GetIsHit() { return m_isHit; }			  // m_isHitのゲッター

    bool SetIsHitTRUE() { return m_isHit = true; }   // m_isHitのセッター　true
    bool SetIsHitFALSE() { return m_isHit = false; } // m_isHitのセッター  false
};