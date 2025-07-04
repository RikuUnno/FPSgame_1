#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(const std::variant<BoxType, SphereType, CapsuleType>& data, CollisionManager* manager)
    : type((ColliderType)data.index()), data(data), m_manager(manager)
{
#ifdef _DEBUG
    printfDx("cns ");
#endif // _DEBUG

    m_isHit = false;
    aabb = { VGet(0, 0, 0), VGet(0, 0, 0) };
    m_manager->AddCollider(this);
}

Collider::~Collider()
{
#ifdef _DEBUG
    printfDx("OUT ");
#endif // _DEBUG

    m_manager->DeleteCollider(this);
}

// m_isHit�̃Z�b�^�[�@true
void Collider::SetIsHitTRUE()
{
	m_isHit = true;
}

// m_isHit�̃Z�b�^�[�@false
void Collider::SetIsHitFALSE()
{
	m_isHit = false;
}

void Collider::AddCurrentHitCollider(Collider* col)
{
    currentHitColliders.push_back(col);
}

#ifdef _DEBUG
// �f�o�b�N�p��AABB����ŕ\��
void Collider::DrawAABB() const
{
    int color = GetColor(255, 255, 255);

    VECTOR p[8] = {
        VGet(aabb.min.x, aabb.min.y, aabb.min.z),
        VGet(aabb.max.x, aabb.min.y, aabb.min.z),
        VGet(aabb.max.x, aabb.max.y, aabb.min.z),
        VGet(aabb.min.x, aabb.max.y, aabb.min.z),
        VGet(aabb.min.x, aabb.min.y, aabb.max.z),
        VGet(aabb.max.x, aabb.min.y, aabb.max.z),
        VGet(aabb.max.x, aabb.max.y, aabb.max.z),
        VGet(aabb.min.x, aabb.max.y, aabb.max.z)
    };

    // ����`��
    DrawLine3D(p[0], p[1], color); DrawLine3D(p[1], p[2], color);
    DrawLine3D(p[2], p[3], color); DrawLine3D(p[3], p[0], color);
    DrawLine3D(p[4], p[5], color); DrawLine3D(p[5], p[6], color);
    DrawLine3D(p[6], p[7], color); DrawLine3D(p[7], p[4], color);
    DrawLine3D(p[0], p[4], color); DrawLine3D(p[1], p[5], color);
    DrawLine3D(p[2], p[6], color); DrawLine3D(p[3], p[7], color);
}
#endif // _DEBUG

void Collider::CheckCollisionEvent()
{
    for (Collider* other : currentHitColliders)
    {
        if (std::find(previousHitColliders.begin(), previousHitColliders.end(), other) == previousHitColliders.end())
        {
            OnCollisionEnter(other); // ���߂ē�������
        }
        else
        {
            OnCollisionStay(other); // �O�������������Ă�
        }
    }

    for (Collider* other : previousHitColliders)
    {
        if (std::find(currentHitColliders.begin(), currentHitColliders.end(), other) == currentHitColliders.end())
        {
            OnCollisionExit(other); // ����͓������Ă��Ȃ�
        }
    }

    previousHitColliders = currentHitColliders; // �O�̏�Ԃ��X�V
    currentHitColliders.clear(); // ���̏�Ԃ͏�����
}