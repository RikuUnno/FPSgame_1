#pragma once
#include "DxLib.h"
#include <variant>

class CollisionManager; // 前方宣言

enum class ColliderType // Colliderの分別
{
    Box,
    Sphere,
    Capsule
};

struct BoxType {               // AABB兼Box
    VECTOR min; // 最小座標
    VECTOR max; // 最大座標
}typedef AABB;

struct SphereType           // 球    
{
    VECTOR m_spherePos; // 球の中心点
    double m_radius;	// 円の半径
};

struct CapsuleType          // カプセル
{
    VECTOR m_posTop;     // カプセルの上端
    VECTOR m_posBottom;  // カプセルの下端
    double m_height;     // カプセルの高さ
    double m_radius;     // カプセルの半径
};

class Collider
{
protected:
    bool m_isHit;       // 衝突したらtrue
    AABB aabb;

    ColliderType type;

    std::variant<BoxType, SphereType, CapsuleType> data;

    CollisionManager* m_manager;

public:
    // コンストラクタ
    //Collider(const BoxType& box, CollisionManager* manager);

    //Collider(const SphereType& sphere, CollisionManager* manager);

    //Collider(const CapsuleType& capsule, CollisionManager* manager);

    Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, CollisionManager* manager);

    // デストラクタ
    virtual ~Collider();

    // m_isHitのセッター　true
    void SetIsHitTRUE();
    // m_isHitのセッター　false
    void SetIsHitFALSE();

    virtual void SetAABB() = 0; // 各コライダーに実装内容を描く

    AABB GetAABB() const { return aabb; } // AABBのゲッター
    ColliderType GetType() const { return type; } // 構造体のTypeを返す
    bool GetIsHit() { return m_isHit; }			  // m_isHitのゲッター

    const BoxType* GetBox() const { return std::get_if<BoxType>(&data); } // BoxTypeのゲッター
    const SphereType* GetSphere() const { return std::get_if<SphereType>(&data); } // SphereTypeのゲッター
    const CapsuleType* GetCapsule() const { return std::get_if<CapsuleType>(&data); } // CapsuleTypeのゲッター

    void AddCollider(CollisionManager* manager); // Coliderの追加

    void DrawAABB() const;
};
 