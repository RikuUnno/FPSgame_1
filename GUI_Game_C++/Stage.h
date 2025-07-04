#pragma once
#include "DxLib.h"
#include "BoxCollider.h"

class Stage
	: public BoxCollider
{
private:
	unsigned int m_color; // �{�b�N�X�̐F

public:
	Stage(VECTOR min, VECTOR max, unsigned int color, CollisionManager* manager); // �R���X�g���N�^
	virtual ~Stage();									      // �f�X�g���N�^

	Stage(const Stage& ohter);

public:
	void Update();			// �X�V
	void DrawStage() const;	// �`��
};