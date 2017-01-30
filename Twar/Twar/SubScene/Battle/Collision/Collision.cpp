/**
@file Collision.cpp
@brief Collisionクラス実装
@author kawaguchi
*/

#include <d3dx9.h>
#include "../Ship/ShipManager.h"
#include "Collision.h"

Collision::Collision(ShipManager* a_pShipManager)
{
}

Collision::~Collision()
{
}

bool Collision::CheckFirstCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float r1, float r2)
{
	if ((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.z - pos2.z) * (pos1.z - pos2.z) <= (r1 + r2) * (r1 + r2))
	{
		return true;
	}
	return false;
}

bool Collision::CheckSecondCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, ShipManager::ShipSize shipSize1, ShipManager::ShipSize shipSize2, float rotate1, float rotate2)
{
	CollisionPosXY CollisionPosXY1[6];
	CollisionPosXY CollisionPosXY2[6];

	CreateShipCollisionPos(pos1, shipSize1, rotate1, CollisionPosXY1);
	CreateShipCollisionPos(pos2, shipSize2, rotate2, CollisionPosXY2);

	for (int i = 0; i < 4; i++)
	{

		CollisionPosXY A = CollisionPosXY1[i];
		CollisionPosXY B = CollisionPosXY1[i + 1];
		CollisionPosXY C = CollisionPosXY1[i + 2];

		for (int j = 0; j < 6; j++)
		{
			CollisionPosXY P = CollisionPosXY2[j];

			CollisionPosXY AB = SubCheckSecondCollision(B, A);
			CollisionPosXY BP = SubCheckSecondCollision(P, B);

			CollisionPosXY BC = SubCheckSecondCollision(C, B);
			CollisionPosXY CP = SubCheckSecondCollision(P, C);

			CollisionPosXY CA = SubCheckSecondCollision(A, C);
			CollisionPosXY AP = SubCheckSecondCollision(P, A);

			double z1 = AB.x * BP.y - AB.y * BP.x;
			double z2 = BC.x * CP.y - BC.y * CP.x;
			double z3 = CA.x * AP.y - CA.y * AP.x;

			if ((z1 > 0 && z2 > 0 && z3 > 0) || (z1 < 0 && z2 < 0 && z3 < 0))
			{
				return true;
			}
		}
	}
	return false;
}

Collision::CollisionPosXY Collision::SubCheckSecondCollision(CollisionPosXY a, CollisionPosXY b)
{
	CollisionPosXY ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;

	return ret;
}

void Collision::CreateShipCollisionPos(D3DXVECTOR3 objPos, ShipManager::ShipSize shipSize, float rotate, CollisionPosXY* collisionPosXY)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, rotate * 3.141592f / 180.f);

	D3DXVECTOR3 vec1{ shipSize.m_MaxX, 0.f, 0.f };
	D3DXVECTOR3 vec2{ shipSize.m_MaxX / 3.f, 0.f, shipSize.m_MaxZ };
	D3DXVECTOR3 vec3{ shipSize.m_MaxX / 3.f, 0.f, shipSize.m_MinZ };
	D3DXVECTOR3 vec4{ shipSize.m_MinX / 3.f, 0.f, shipSize.m_MaxZ };
	D3DXVECTOR3 vec5{ shipSize.m_MinX / 3.f, 0.f, shipSize.m_MinZ };
	D3DXVECTOR3 vec6{ shipSize.m_MinX, 0.f, 0.f };
	D3DXVec3TransformCoord(&vec1, &vec1, &rotation);
	D3DXVec3TransformCoord(&vec2, &vec2, &rotation);
	D3DXVec3TransformCoord(&vec3, &vec3, &rotation);
	D3DXVec3TransformCoord(&vec4, &vec4, &rotation);
	D3DXVec3TransformCoord(&vec5, &vec5, &rotation);
	D3DXVec3TransformCoord(&vec6, &vec6, &rotation);


	collisionPosXY[0].x = objPos.x + vec1.x;
	collisionPosXY[0].y = objPos.z + vec1.z;
	collisionPosXY[1].x = objPos.x + vec2.x;
	collisionPosXY[1].y = objPos.z + vec2.z;
	collisionPosXY[2].x = objPos.x + vec3.x;
	collisionPosXY[2].y = objPos.z + vec3.z;
	collisionPosXY[3].x = objPos.x + vec4.x;
	collisionPosXY[3].y = objPos.z + vec4.z;
	collisionPosXY[4].x = objPos.x + vec5.x;
	collisionPosXY[4].y = objPos.z + vec5.z;
	collisionPosXY[5].x = objPos.x + vec6.x;
	collisionPosXY[5].y = objPos.z + vec6.z;
}
