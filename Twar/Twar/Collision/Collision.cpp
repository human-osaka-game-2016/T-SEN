
#include "Collision.h"
#include "CollisionManager.h"


Collision::Collision(float radius)
	: m_Radius(radius)
	, m_IsExist(false)
{
}


Collision::~Collision()
{
}

// 座標セット
void Collision::SetData(const D3DXVECTOR3& pos)
{
	m_IsExist = false;
	m_Pos = pos;
	CollisionManager::Instance().SetCollision(this);
}

void Collision::CheckState()
{
	m_IsExist = true;
}

