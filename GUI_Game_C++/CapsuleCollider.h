#pragma once
#include <DxLib.h>
#include "Collider.h"

// カプセル型コライダー
class CapsuleCollider
    : public Collider
{
protected:
    CapsuleCollider(VECTOR top, VECTOR bottom, double height, double radius, CollisionManager* manager); // コンストラクタ

    virtual ~CapsuleCollider(); // デストラクタ

public:
    VECTOR GetTop() const { return std::get<CapsuleType>(data).m_posTop; }       // m_posTopのゲッター
    VECTOR GetBottom() const { return std::get<CapsuleType>(data).m_posBottom; } // m_posBottomのゲッター
    double Getheight() const { return std::get<CapsuleType>(data).m_height; }    // m_heightのゲッター
    double GetRadius() const { return std::get<CapsuleType>(data).m_radius; }    // m_radiusのゲッター

    void SetAABB() override; // AABBの設定
};