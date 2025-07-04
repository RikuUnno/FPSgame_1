#pragma once
#include "DxLib.h"
#include "BoxCollider.h"

class Stage
	: public BoxCollider
{
private:
	unsigned int m_color; // ボックスの色

public:
	Stage(VECTOR min, VECTOR max, unsigned int color, CollisionManager* manager); // コンストラクタ
	virtual ~Stage();									      // デストラクタ

	Stage(const Stage& ohter);

public:
	void Update();			// 更新
	void DrawStage() const;	// 描画
};