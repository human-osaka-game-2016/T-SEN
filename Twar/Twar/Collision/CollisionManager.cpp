
//-------------------------------------------------------------------------------------------------------------------------------------//
//includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "CollisionManager.h"
#include "Collision.h"
#include <d3dx9.h>

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::SetCollision(Collision* collision)
{
	m_Collision.emplace_back(collision);
}

void CollisionManager::CheckCollision()
{
	if(m_Collision.size() > 1)
	{
		for(unsigned int i = 0; i < (m_Collision.size() - 1); i++)
		{
			for(unsigned int j = 1; j < m_Collision.size(); j++)
			{
				if(m_Collision[i] == m_Collision[j])
				{
					continue;
				}

				D3DXVECTOR3 vecLength = (m_Collision[j]->GetPos()) - (m_Collision[i]->GetPos());
				float fLength = D3DXVec3Length(&vecLength);
				float radius = (m_Collision[i]->GetRadius()) + (m_Collision[j]->GetRadius());
				if(fLength < radius)
				{
					if(m_Collision[i]->GetID() != m_Collision[j]->GetID())
					{
						m_Collision[i]->CheckState();
						m_Collision[j]->CheckState();
					}
				}
			}

		}
	}
}

void CollisionManager::ClearData()
{
	m_Collision.clear();
}