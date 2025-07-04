#pragma once
#include <vector>
#include "DxLib.h"
#include "Collider.h"

class SphereCollider;	// 前方宣言
class CapsuleCollider;	// 前方宣言

class CollisionManager
{
private:
	std::vector<Collider*> colliders; // 全コライダー
	std::vector<std::pair<Collider*, Collider*>> broadPhasePairs;

public:
	CollisionManager(); // コンストラクタ
	virtual ~CollisionManager(); // デストラクタ

public:
	void AddCollider(Collider* c);

	void DeleteCollider(Collider* c);

public:
	void BroadPhase(); // AABBで大まかな当たり判定＆ペアの作成

	void NarrowPhase(); // BroadPhaseで作ったペアの詳細な当たり判定

	void HitCheck(); // 総まとめの関数

	void CheckEvent(); // イベントのチェック

private:

	bool CheckAABB(const AABB& a, const AABB& b); // AABBの判定 兼 BoxとBoxの判定

	bool HitCheckBoxToSphere(const BoxType& b, const SphereType& s); // BoxとSphereの判定

	bool HitCheckBoxToCapsule(const BoxType& b, const CapsuleType& c); // BoxとCapsaleの判定

	bool HitCheckSphereToSphere(const SphereType& s1, const SphereType& s2); // SphereとSphereの判定

	bool HitCheckSphereToCapsule(const SphereType& s, const CapsuleType& c); // SphereとCapsaleの判定

	bool HitCheckCapsuleToCapsule(const CapsuleType& c1, const CapsuleType& c2); // CapsaleとCapsaleの判定

private:
	// 当たり判定用の補助関数
	// 線分同士の最近距離²を求める
	double SegmentSegmentDistSq(const VECTOR& p1, const VECTOR& q1, const VECTOR& p2, const VECTOR& q2);

	// 点と線分の距離²を求める
	double PointToSegmentDistSq(const VECTOR& p, const VECTOR& a, const VECTOR& b);

	// 点とAABBの距離²を計算（点がAABB内なら0）
	double PointToAABBDistSq(const VECTOR& p, const BoxType& box);

	// 線分とAABBの距離²を計算
	double SegmentAABBDistSq(const VECTOR& p1, const VECTOR& p2, const BoxType& box);

public:
	std::vector<Collider*>& GetColliderList() { return colliders; } // allColliderlistのゲッター
};
