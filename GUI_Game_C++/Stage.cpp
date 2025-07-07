#include "Stage.h"

Stage::Stage(VECTOR min, VECTOR max, unsigned int color, CollisionManager* manager)
    :BoxCollider(min, max, manager), m_color(color)
{}

Stage::~Stage()
{}

Stage::Stage(const Stage& ohter)
    :BoxCollider(ohter.GetBox()->min, ohter.GetBox()->max, ohter.m_manager), 
    m_color(ohter.m_color)
{}

void Stage::Update()
{
	SetAABB(); // AABBの更新

    DrawStage();
}

void Stage::DrawStage() const
{
    const BoxType& box = std::get<BoxType>(data);

    // 8頂点を定義
    VECTOR p[8] = {
        VGet(box.min.x, box.min.y, box.min.z),
        VGet(box.max.x, box.min.y, box.min.z),
        VGet(box.max.x, box.max.y, box.min.z),
        VGet(box.min.x, box.max.y, box.min.z),
        VGet(box.min.x, box.min.y, box.max.z),
        VGet(box.max.x, box.min.y, box.max.z),
        VGet(box.max.x, box.max.y, box.max.z),
        VGet(box.min.x, box.max.y, box.max.z)
    };

    // 面で塗りつぶし（床など）
    DrawTriangle3D(p[0], p[1], p[2], m_color, TRUE);
    DrawTriangle3D(p[0], p[2], p[3], m_color, TRUE);

    DrawTriangle3D(p[4], p[5], p[6], m_color, TRUE);
    DrawTriangle3D(p[4], p[6], p[7], m_color, TRUE);

    DrawTriangle3D(p[0], p[1], p[5], m_color, TRUE);
    DrawTriangle3D(p[0], p[5], p[4], m_color, TRUE);

    DrawTriangle3D(p[1], p[2], p[6], m_color, TRUE);
    DrawTriangle3D(p[1], p[6], p[5], m_color, TRUE);

    DrawTriangle3D(p[2], p[3], p[7], m_color, TRUE);
    DrawTriangle3D(p[2], p[7], p[6], m_color, TRUE);

    DrawTriangle3D(p[3], p[0], p[4], m_color, TRUE);
    DrawTriangle3D(p[3], p[4], p[7], m_color, TRUE);

    DrawAABB(); // みやすくするため

}