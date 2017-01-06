
//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "Collision.h"
#include "CollisionManager.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

Collision::Collision(float radius, COLLISION_ID id)
	: m_Radius(radius)
	, m_IsExist(false)
	, m_ID(id)
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

bool Collision::InformCollision()
{
	if(m_IsExist)
	{
		m_IsExist = false;
		return true;
	}
	return false;
}
