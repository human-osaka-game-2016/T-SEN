/**
@file Collision.cpp
@brief Collisionクラス実装
@author kawaguchi
*/

#include <d3dx9.h>
#include <math.h>
#include "../Ship/ShipManager.h"
#include "../Monster/MonsterManager.h"
#include "../Bullet/BulletManager.h"
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

bool Collision::CheckSecondCollisionShipShip(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, ShipManager::ShipSize shipSize1, ShipManager::ShipSize shipSize2, float rotate1, float rotate2)
{
	D3DXVECTOR2 CollisionPosXY1[6];
	D3DXVECTOR2 CollisionPosXY2[6];

	CreateShipCollisionPos2D(pos1, shipSize1, rotate1, CollisionPosXY1);
	CreateShipCollisionPos2D(pos2, shipSize2, rotate2, CollisionPosXY2);

	for (int i = 0; i < 4; i++)
	{

		D3DXVECTOR2 A = CollisionPosXY1[i];
		D3DXVECTOR2 B = CollisionPosXY1[i + 1];
		D3DXVECTOR2 C = CollisionPosXY1[i + 2];

		for (int j = 0; j < 6; j++)
		{
			D3DXVECTOR2 P = CollisionPosXY2[j];

			D3DXVECTOR2 AB = SubCheckSecondCollision(B, A);
			D3DXVECTOR2 BP = SubCheckSecondCollision(P, B);

			D3DXVECTOR2 BC = SubCheckSecondCollision(C, B);
			D3DXVECTOR2 CP = SubCheckSecondCollision(P, C);

			D3DXVECTOR2 CA = SubCheckSecondCollision(A, C);
			D3DXVECTOR2 AP = SubCheckSecondCollision(P, A);

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

bool Collision::CheckSecondCollisionShipMonster(D3DXVECTOR3 shipPos, D3DXVECTOR3 monsterPos, ShipManager::ShipSize shipSize, MonsterManager::MonsterSize monsterSize, float shipRotate)
{
	D3DXVECTOR2 CollisionPosXY[6];

	CreateShipCollisionPos2D(shipPos, shipSize, shipRotate, CollisionPosXY);

	for (char i = 0; i < 6; i++)
	{
		if ((CollisionPosXY[i].x - monsterPos.x) * (CollisionPosXY[i].x - monsterPos.x) + (CollisionPosXY[i].y - monsterPos.z) * (CollisionPosXY[i].y - monsterPos.z) <= (monsterSize.m_MaxR * 1.5f) * (monsterSize.m_MaxR * 1.5f)) // 2 はモンスターの拡大率
		{
			return true;
		}
	}
	return false;
}

D3DXVECTOR2 Collision::SubCheckSecondCollision(D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	D3DXVECTOR2 ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;

	return ret;
}

bool Collision::CheckFirstCollision3D(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float r1, float r2)
{
	if ((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) + (pos2.z - pos1.z) * (pos2.z - pos1.z) <= (r1 + r2) * (r1 + r2))
	{
		return true;
	}
	return false;
}

bool Collision::CheckSecondCollisionShipBullet(D3DXVECTOR3 shipPos, D3DXVECTOR3 oldBulletPos, D3DXVECTOR3 newBulletPos, ShipManager::ShipSize shipSize, BulletManager::BulletSize bulletSize, float shipRotate, float bulletRotate)
{
	D3DXVECTOR3 ShipCollisionPosXYZ[6];
//	D3DXVECTOR3 oldBulletD3DXVECTOR3[8];
//	D3DXVECTOR3 newBulletD3DXVECTOR3[8];

	CreateShipCollisionPos3D(shipPos, shipSize, shipRotate, ShipCollisionPosXYZ);
//	CreateBulletCollisionPos3D(oldBulletPos, bulletSize, bulletRotate, oldBulletD3DXVECTOR3);
//	CreateBulletCollisionPos3D(newBulletPos, bulletSize, bulletRotate, newBulletD3DXVECTOR3);

	D3DXVECTOR3 vec1;
	D3DXVECTOR3 vec2;
	D3DXVECTOR3 normalVec;
	D3DXVECTOR3 innerVec1;
	D3DXVECTOR3 innerVec2;
	D3DXVECTOR3 contactPoint;

	for (char i = 0; i < 4; i++)
	{
		vec1 = { oldBulletPos.x - ShipCollisionPosXYZ[i % 4].x, oldBulletPos.y - ShipCollisionPosXYZ[i % 4].y, oldBulletPos.z - ShipCollisionPosXYZ[i % 4].z };
		vec2 = { newBulletPos.x - ShipCollisionPosXYZ[i % 4].x, newBulletPos.y - ShipCollisionPosXYZ[i % 4].y, newBulletPos.z - ShipCollisionPosXYZ[i % 4].z };
		
		normalVec = CreateNormalVector(ShipCollisionPosXYZ[4], ShipCollisionPosXYZ[(i + 1) % 4], ShipCollisionPosXYZ[i % 4]);
		innerVec1 = InnerProduct(vec1, normalVec);
		innerVec2 = InnerProduct(vec2, normalVec);

		//----------------------------------------------------------------------------------------------------------------------------------------------
		//	&& だと弾のヒット判定が厳しい　|| だとゆるい
		//----------------------------------------------------------------------------------------------------------------------------------------------
		if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
		{
			//	float distance1 = sqrt((innerVec1.x * innerVec1.x) + (innerVec1.y * innerVec1.y) + (innerVec1.z * innerVec1.z)) / sqrt((normalVec.x * normalVec.x) + (normalVec.y * normalVec.y) + (normalVec.z * normalVec.z));
			//	float distance2 = sqrt((innerVec2.x * innerVec2.x) + (innerVec2.y * innerVec2.y) + (innerVec2.z * innerVec2.z)) / sqrt((normalVec.x * normalVec.x) + (normalVec.y * normalVec.y) + (normalVec.z * normalVec.z));
			//	return true;
			//}

			CreateContactPoint(&contactPoint, &ShipCollisionPosXYZ[4], &normalVec, &vec1, &vec2);

			if (contactPoint != NULL)
			{
				if (IsPointInPolygon(&contactPoint, &ShipCollisionPosXYZ[4], &ShipCollisionPosXYZ[(i + 1) % 4], &ShipCollisionPosXYZ[i % 4]))
				{
					return true;
				}
			}
		}

		normalVec = CreateNormalVector(ShipCollisionPosXYZ[5], ShipCollisionPosXYZ[i % 4], ShipCollisionPosXYZ[(i + 1) % 4]);
		innerVec1 = InnerProduct(vec1, normalVec);
		innerVec2 = InnerProduct(vec2, normalVec);

		//----------------------------------------------------------------------------------------------------------------------------------------------
		//	&& だと弾のヒット判定が厳しい　|| だとゆるい
		//----------------------------------------------------------------------------------------------------------------------------------------------
		if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
		{
			//	return true;
			//}

			CreateContactPoint(&contactPoint, &ShipCollisionPosXYZ[5], &normalVec, &vec1, &vec2);

			if (contactPoint != NULL)
			{
				if (IsPointInPolygon(&contactPoint, &ShipCollisionPosXYZ[5], &ShipCollisionPosXYZ[i % 4], &ShipCollisionPosXYZ[(i + 1) % 4]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Collision::CheckSecondCollisionMonsterBullet(D3DXVECTOR3 monsterPos, D3DXVECTOR3 oldBulletPos, D3DXVECTOR3 newBulletPos, MonsterManager::MonsterSize monsterSize, BulletManager::BulletSize bulletSize, float monsterRotate, float bulletRotate)
{
	D3DXVECTOR3 MonsterCollisionPosXYZ[8];

	CreateMonsterCollisionPos3D(monsterPos, monsterSize, monsterRotate, MonsterCollisionPosXYZ);

	D3DXVECTOR3 vec1;
	D3DXVECTOR3 vec2;
	D3DXVECTOR3 normalVec;
	D3DXVECTOR3 innerVec1;
	D3DXVECTOR3 innerVec2;
	D3DXVECTOR3 contactPoint;

	for (char i = 0; i < 4; i++)
	{
		vec1 = { oldBulletPos.x - MonsterCollisionPosXYZ[i].x, oldBulletPos.y - MonsterCollisionPosXYZ[i].y, oldBulletPos.z - MonsterCollisionPosXYZ[i].z };
		vec2 = { newBulletPos.x - MonsterCollisionPosXYZ[i].x, newBulletPos.y - MonsterCollisionPosXYZ[i].y, newBulletPos.z - MonsterCollisionPosXYZ[i].z };

		switch (i)
		{
		case 0:
		case 2:
			normalVec = CreateNormalVector(MonsterCollisionPosXYZ[i], MonsterCollisionPosXYZ[(i % 4) + 4], MonsterCollisionPosXYZ[((i + 1) % 4) + 4]);
			innerVec1 = InnerProduct(vec1, normalVec);
			innerVec2 = InnerProduct(vec2, normalVec);

			//----------------------------------------------------------------------------------------------------------------------------------------------
			//	&& だと弾のヒット判定が厳しい　|| だとゆるい
			//----------------------------------------------------------------------------------------------------------------------------------------------
			if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
			{
				//return true;
				//}

				CreateContactPoint(&contactPoint, &MonsterCollisionPosXYZ[i], &normalVec, &vec1, &vec2);

				if (contactPoint != NULL)
				{
					if (IsPointInPolygon(&contactPoint, &MonsterCollisionPosXYZ[i], &MonsterCollisionPosXYZ[(i % 4) + 4], &MonsterCollisionPosXYZ[((i + 1) % 4) + 4]))
					{
						return true;
					}
				}
			}

			normalVec = CreateNormalVector(MonsterCollisionPosXYZ[i], MonsterCollisionPosXYZ[((i + 1) % 4) + 4], MonsterCollisionPosXYZ[((i + 2) % 4) + 4]);
			innerVec1 = InnerProduct(vec1, normalVec);
			innerVec2 = InnerProduct(vec2, normalVec);

			//----------------------------------------------------------------------------------------------------------------------------------------------
			//	&& だと弾のヒット判定が厳しい　|| だとゆるい
			//----------------------------------------------------------------------------------------------------------------------------------------------
			if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
			{
				//	return true;
				//}

				CreateContactPoint(&contactPoint, &MonsterCollisionPosXYZ[i], &normalVec, &vec1, &vec2);

				if (contactPoint != NULL)
				{
					if (IsPointInPolygon(&contactPoint, &MonsterCollisionPosXYZ[i], &MonsterCollisionPosXYZ[((i + 1) % 4) + 4], &MonsterCollisionPosXYZ[((i + 2) % 4) + 4]))
					{
						return true;
					}
				}
			}

			normalVec = CreateNormalVector(MonsterCollisionPosXYZ[i], MonsterCollisionPosXYZ[((i + 2) % 4) + 4], MonsterCollisionPosXYZ[(i % 4) + 4]);
			innerVec1 = InnerProduct(vec1, normalVec);
			innerVec2 = InnerProduct(vec2, normalVec);

			//----------------------------------------------------------------------------------------------------------------------------------------------
			//	&& だと弾のヒット判定が厳しい　|| だとゆるい
			//----------------------------------------------------------------------------------------------------------------------------------------------
			if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
			{
				//	return true;
				//}

				CreateContactPoint(&contactPoint, &MonsterCollisionPosXYZ[i], &normalVec, &vec1, &vec2);

				if (contactPoint != NULL)
				{
					if (IsPointInPolygon(&contactPoint, &MonsterCollisionPosXYZ[i], &MonsterCollisionPosXYZ[((i + 2) % 4) + 4], &MonsterCollisionPosXYZ[(i % 4) + 4]))
					{
						return true;
					}
				}
			}

		case 1:
		case 3:
			normalVec = CreateNormalVector(MonsterCollisionPosXYZ[i], MonsterCollisionPosXYZ[((i + 1) % 4) + 4], MonsterCollisionPosXYZ[(i % 4) + 4]);
			innerVec1 = InnerProduct(vec1, normalVec);
			innerVec2 = InnerProduct(vec2, normalVec);

			//----------------------------------------------------------------------------------------------------------------------------------------------
			//	&& だと弾のヒット判定が厳しい　|| だとゆるい
			//----------------------------------------------------------------------------------------------------------------------------------------------
			if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
			{
				//	return true;
				//}

				CreateContactPoint(&contactPoint, &MonsterCollisionPosXYZ[i], &normalVec, &vec1, &vec2);

				if (contactPoint != NULL)
				{
					if (IsPointInPolygon(&contactPoint, &MonsterCollisionPosXYZ[i], &MonsterCollisionPosXYZ[((i + 1) % 4) + 4], &MonsterCollisionPosXYZ[(i % 4) + 4]))
					{
						return true;
					}
				}
			}

			normalVec = CreateNormalVector(MonsterCollisionPosXYZ[i], MonsterCollisionPosXYZ[((i + 2) % 4) + 4], MonsterCollisionPosXYZ[((i + 1) % 4) + 4]);
			innerVec1 = InnerProduct(vec1, normalVec);
			innerVec2 = InnerProduct(vec2, normalVec);

			//----------------------------------------------------------------------------------------------------------------------------------------------
			//	&& だと弾のヒット判定が厳しい　|| だとゆるい
			//----------------------------------------------------------------------------------------------------------------------------------------------
			if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
			{
				//	return true;
				//}

				CreateContactPoint(&contactPoint, &MonsterCollisionPosXYZ[i], &normalVec, &vec1, &vec2);

				if (contactPoint != NULL)
				{
					if (IsPointInPolygon(&contactPoint, &MonsterCollisionPosXYZ[i], &MonsterCollisionPosXYZ[((i + 2) % 4) + 4], &MonsterCollisionPosXYZ[((i + 1) % 4) + 4]))
					{
						return true;
					}
				}
			}

			normalVec = CreateNormalVector(MonsterCollisionPosXYZ[i], MonsterCollisionPosXYZ[(i % 4) + 4], MonsterCollisionPosXYZ[(i + 2) + 4]);
			innerVec1 = InnerProduct(vec1, normalVec);
			innerVec2 = InnerProduct(vec2, normalVec);

			//----------------------------------------------------------------------------------------------------------------------------------------------
			//	&& だと弾のヒット判定が厳しい　|| だとゆるい
			//----------------------------------------------------------------------------------------------------------------------------------------------
			if (innerVec1.x * innerVec2.x <= 0 || innerVec1.y * innerVec2.y <= 0 || innerVec1.z * innerVec2.z <= 0)
			{
				//	return true;
				//}

				CreateContactPoint(&contactPoint, &MonsterCollisionPosXYZ[i], &normalVec, &vec1, &vec2);

				if (contactPoint != NULL)
				{
					if (IsPointInPolygon(&contactPoint, &MonsterCollisionPosXYZ[i], &MonsterCollisionPosXYZ[(i % 4) + 4], &MonsterCollisionPosXYZ[(i + 2) + 4]))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

D3DXVECTOR3 Collision::CreateNormalVector(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3)
{
	D3DXVECTOR3 vector12 = { pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z };
	D3DXVECTOR3 vector23 = { pos3.x - pos2.x, pos3.y - pos2.y, pos3.z - pos2.z };
	D3DXVECTOR3 normalVector = CrossProduct(vector12, vector23);
	return normalVector;
}

D3DXVECTOR3 Collision::InnerProduct(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	D3DXVECTOR3 innnerVec = { vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z };
	return innnerVec;
}

D3DXVECTOR3 Collision::CrossProduct(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	D3DXVECTOR3 crossVec = { (vec1.y * vec2.z) - (vec2.y * vec1.z),
								 (-1 * (vec1.x * vec2.z) - (vec2.x * vec1.z)),
								 (vec1.x * vec2.y) - (vec2.x * vec1.y)};
	return crossVec;
}

void Collision::CreateContactPoint(D3DXVECTOR3* pOut, D3DXVECTOR3* pPoint, D3DXVECTOR3* pNormal, D3DXVECTOR3* pVec1, D3DXVECTOR3* pVec2)
{
	D3DXPLANE plane;
	D3DXPlaneFromPointNormal(&plane, pPoint, pNormal);
	D3DXPlaneIntersectLine(pOut, &plane, pVec1, pVec2);
}

bool Collision::IsPointInPolygon(D3DXVECTOR3* pPoint, D3DXVECTOR3* pPosA, D3DXVECTOR3* pPosB, D3DXVECTOR3* pPosC)
{
	D3DXVECTOR3 AB, BC, CA, AP, BP, CP;
	CreateVectorAtoB(&AB, pPosA, pPosB);
	CreateVectorAtoB(&BC, pPosB, pPosC);
	CreateVectorAtoB(&CA, pPosC, pPosA);
	CreateVectorAtoB(&AP, pPosA, pPoint);
	CreateVectorAtoB(&BP, pPosB, pPoint);
	CreateVectorAtoB(&CP, pPosC, pPoint);

	D3DXVECTOR3 crossABP, crossBCP, crossCAP;
	D3DXVec3Cross(&crossABP, &AB, &BP);
	D3DXVec3Cross(&crossBCP, &BC, &CP);
	D3DXVec3Cross(&crossCAP, &CA, &AP);

	if ((crossABP.x * crossBCP.x <= 0 && crossABP.y * crossBCP.y <= 0 && crossABP.z * crossBCP.z <= 0) ||
		(crossABP.x * crossCAP.x <= 0 && crossABP.y * crossCAP.y <= 0 && crossCAP.z * crossCAP.z <= 0))
	{
		return false;
	}
	return true;
}

D3DXVECTOR3* Collision::CreateVectorAtoB(D3DXVECTOR3* pOut, D3DXVECTOR3* pA, D3DXVECTOR3* pB)
{
	pOut->x = pB->x - pA->x;
	pOut->y = pB->y - pA->y;
	pOut->z = pB->z - pA->z;
	return pOut;
}

void Collision::CreateShipCollisionPos2D(D3DXVECTOR3 objPos, ShipManager::ShipSize shipSize, float rotate, D3DXVECTOR2* CollisionPosXY)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, rotate * 3.141592f / 180.f);

	D3DXVECTOR3 vec1{ 0.f, 0.f, shipSize.m_MaxZ };
	D3DXVECTOR3 vec2{ shipSize.m_MaxX, 0.f, shipSize.m_MaxZ / 3.f };
	D3DXVECTOR3 vec3{ shipSize.m_MinX, 0.f, shipSize.m_MaxZ / 3.f };
	D3DXVECTOR3 vec4{ shipSize.m_MaxX, 0.f, shipSize.m_MinZ / 3.f };
	D3DXVECTOR3 vec5{ shipSize.m_MinX, 0.f, shipSize.m_MinZ / 3.f };
	D3DXVECTOR3 vec6{ 0.f, 0.f, shipSize.m_MinZ };
	D3DXVec3TransformCoord(&vec1, &vec1, &rotation);
	D3DXVec3TransformCoord(&vec2, &vec2, &rotation);
	D3DXVec3TransformCoord(&vec3, &vec3, &rotation);
	D3DXVec3TransformCoord(&vec4, &vec4, &rotation);
	D3DXVec3TransformCoord(&vec5, &vec5, &rotation);
	D3DXVec3TransformCoord(&vec6, &vec6, &rotation);


	CollisionPosXY[0].x = objPos.x + vec1.x;
	CollisionPosXY[0].y = objPos.z + vec1.z;
	CollisionPosXY[1].x = objPos.x + vec2.x;
	CollisionPosXY[1].y = objPos.z + vec2.z;
	CollisionPosXY[2].x = objPos.x + vec3.x;
	CollisionPosXY[2].y = objPos.z + vec3.z;
	CollisionPosXY[3].x = objPos.x + vec4.x;
	CollisionPosXY[3].y = objPos.z + vec4.z;
	CollisionPosXY[4].x = objPos.x + vec5.x;
	CollisionPosXY[4].y = objPos.z + vec5.z;
	CollisionPosXY[5].x = objPos.x + vec6.x;
	CollisionPosXY[5].y = objPos.z + vec6.z;
}

void Collision::CreateShipCollisionPos3D(D3DXVECTOR3 objPos, ShipManager::ShipSize shipSize, float rotate, D3DXVECTOR3* D3DXVECTOR2Z)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, rotate * 3.141592f / 180.f);

	D3DXVECTOR3 vec1{ 0.f, 0.f, shipSize.m_MaxZ };
	D3DXVECTOR3 vec2{ shipSize.m_MaxX, 0.f, 0.f };
	D3DXVECTOR3 vec3{ 0.f, 0.f, shipSize.m_MinZ };
	D3DXVECTOR3 vec4{ shipSize.m_MinX, 0.f, 0.f };
	D3DXVECTOR3 vec5{ 0.f, shipSize.m_MaxY, 0.f };
	D3DXVECTOR3 vec6{ 0.f, shipSize.m_MinY, 0.f };
	D3DXVec3TransformCoord(&vec1, &vec1, &rotation);
	D3DXVec3TransformCoord(&vec2, &vec2, &rotation);
	D3DXVec3TransformCoord(&vec3, &vec3, &rotation);
	D3DXVec3TransformCoord(&vec4, &vec4, &rotation);
	D3DXVec3TransformCoord(&vec5, &vec5, &rotation);
	D3DXVec3TransformCoord(&vec6, &vec6, &rotation);


	D3DXVECTOR2Z[0].x = objPos.x + vec1.x;
	D3DXVECTOR2Z[0].y = objPos.y + vec1.y;
	D3DXVECTOR2Z[0].z = objPos.z + vec1.z;
	D3DXVECTOR2Z[1].x = objPos.x + vec2.x;
	D3DXVECTOR2Z[1].y = objPos.y + vec2.y;
	D3DXVECTOR2Z[1].z = objPos.z + vec2.z;
	D3DXVECTOR2Z[2].x = objPos.x + vec3.x;
	D3DXVECTOR2Z[2].y = objPos.y + vec3.y;
	D3DXVECTOR2Z[2].z = objPos.z + vec3.z;
	D3DXVECTOR2Z[3].x = objPos.x + vec4.x;
	D3DXVECTOR2Z[3].y = objPos.y + vec4.y;
	D3DXVECTOR2Z[3].z = objPos.z + vec4.z;
	D3DXVECTOR2Z[4].x = objPos.x + vec5.x;
	D3DXVECTOR2Z[4].y = objPos.y + vec5.y;
	D3DXVECTOR2Z[4].z = objPos.z + vec5.z;
	D3DXVECTOR2Z[5].x = objPos.x + vec6.x;
	D3DXVECTOR2Z[5].y = objPos.y + vec6.y;
	D3DXVECTOR2Z[5].z = objPos.z + vec6.z;
}

void Collision::CreateBulletCollisionPos3D(D3DXVECTOR3 objPos, BulletManager::BulletSize bulletSize, float rotate, D3DXVECTOR3* D3DXVECTOR2Z)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, rotate * 3.141592f / 180.f);

	D3DXVECTOR3 vec1{ bulletSize.m_MaxX, bulletSize.m_MaxY, bulletSize.m_MaxZ };
	D3DXVECTOR3 vec2{ bulletSize.m_MaxX, bulletSize.m_MaxY, bulletSize.m_MinZ };
	D3DXVECTOR3 vec3{ bulletSize.m_MinX, bulletSize.m_MaxY, bulletSize.m_MinZ };
	D3DXVECTOR3 vec4{ bulletSize.m_MinX, bulletSize.m_MaxY, bulletSize.m_MaxZ };
	D3DXVECTOR3 vec5{ bulletSize.m_MaxX, bulletSize.m_MinY, bulletSize.m_MaxZ };
	D3DXVECTOR3 vec6{ bulletSize.m_MaxX, bulletSize.m_MinY, bulletSize.m_MinZ };
	D3DXVECTOR3 vec7{ bulletSize.m_MinX, bulletSize.m_MinY, bulletSize.m_MinZ };
	D3DXVECTOR3 vec8{ bulletSize.m_MinX, bulletSize.m_MinY, bulletSize.m_MaxZ };
	D3DXVec3TransformCoord(&vec1, &vec1, &rotation);
	D3DXVec3TransformCoord(&vec2, &vec2, &rotation);
	D3DXVec3TransformCoord(&vec3, &vec3, &rotation);
	D3DXVec3TransformCoord(&vec4, &vec4, &rotation);
	D3DXVec3TransformCoord(&vec5, &vec5, &rotation);
	D3DXVec3TransformCoord(&vec6, &vec6, &rotation);
	D3DXVec3TransformCoord(&vec7, &vec7, &rotation);
	D3DXVec3TransformCoord(&vec8, &vec8, &rotation);


	D3DXVECTOR2Z[0].x = objPos.x + vec1.x;
	D3DXVECTOR2Z[0].y = objPos.y + vec1.y;
	D3DXVECTOR2Z[0].z = objPos.z + vec1.z;
	D3DXVECTOR2Z[1].x = objPos.x + vec2.x;
	D3DXVECTOR2Z[1].y = objPos.y + vec2.y;
	D3DXVECTOR2Z[1].z = objPos.z + vec2.z;
	D3DXVECTOR2Z[2].x = objPos.x + vec3.x;
	D3DXVECTOR2Z[2].y = objPos.y + vec3.y;
	D3DXVECTOR2Z[2].z = objPos.z + vec3.z;
	D3DXVECTOR2Z[3].x = objPos.x + vec4.x;
	D3DXVECTOR2Z[3].y = objPos.y + vec4.y;
	D3DXVECTOR2Z[3].z = objPos.z + vec4.z;
	D3DXVECTOR2Z[4].x = objPos.x + vec5.x;
	D3DXVECTOR2Z[4].y = objPos.y + vec5.y;
	D3DXVECTOR2Z[4].z = objPos.z + vec5.z;
	D3DXVECTOR2Z[5].x = objPos.x + vec6.x;
	D3DXVECTOR2Z[5].y = objPos.y + vec6.y;
	D3DXVECTOR2Z[5].z = objPos.z + vec6.z;
	D3DXVECTOR2Z[6].x = objPos.x + vec7.x;
	D3DXVECTOR2Z[6].y = objPos.y + vec7.y;
	D3DXVECTOR2Z[6].z = objPos.z + vec7.z;
	D3DXVECTOR2Z[7].x = objPos.x + vec8.x;
	D3DXVECTOR2Z[7].y = objPos.y + vec8.y;
	D3DXVECTOR2Z[7].z = objPos.z + vec8.z;

}

void Collision::CreateMonsterCollisionPos3D(D3DXVECTOR3 objPos, MonsterManager::MonsterSize monsterSize, float rotate, D3DXVECTOR3* D3DXVECTOR2Z)
{
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, rotate * 3.141592f / 180.f);

	D3DXVECTOR3 vec1{ monsterSize.m_MaxX * 1.5f, monsterSize.m_MaxY * 1.5f, monsterSize.m_MaxZ * 1.5f };
	D3DXVECTOR3 vec2{ monsterSize.m_MaxX * 1.5f, monsterSize.m_MinY * 1.5f, monsterSize.m_MinZ * 1.5f };
	D3DXVECTOR3 vec3{ monsterSize.m_MinX * 1.5f, monsterSize.m_MaxY * 1.5f, monsterSize.m_MinZ * 1.5f };
	D3DXVECTOR3 vec4{ monsterSize.m_MinX * 1.5f, monsterSize.m_MinY * 1.5f, monsterSize.m_MaxZ * 1.5f };
	D3DXVECTOR3 vec5{ monsterSize.m_MinX * 1.5f, monsterSize.m_MaxY * 1.5f, monsterSize.m_MaxZ * 1.5f };
	D3DXVECTOR3 vec6{ monsterSize.m_MaxX * 1.5f, monsterSize.m_MinY * 1.5f, monsterSize.m_MaxZ * 1.5f };
	D3DXVECTOR3 vec7{ monsterSize.m_MaxX * 1.5f, monsterSize.m_MaxY * 1.5f, monsterSize.m_MinZ * 1.5f };
	D3DXVECTOR3 vec8{ monsterSize.m_MinX * 1.5f, monsterSize.m_MinY * 1.5f, monsterSize.m_MinZ * 1.5f };
	D3DXVec3TransformCoord(&vec1, &vec1, &rotation);
	D3DXVec3TransformCoord(&vec2, &vec2, &rotation);
	D3DXVec3TransformCoord(&vec3, &vec3, &rotation);
	D3DXVec3TransformCoord(&vec4, &vec4, &rotation);
	D3DXVec3TransformCoord(&vec5, &vec5, &rotation);
	D3DXVec3TransformCoord(&vec6, &vec6, &rotation);
	D3DXVec3TransformCoord(&vec7, &vec7, &rotation);
	D3DXVec3TransformCoord(&vec8, &vec8, &rotation);


	D3DXVECTOR2Z[0].x = objPos.x + vec1.x;
	D3DXVECTOR2Z[0].y = objPos.y + vec1.y;
	D3DXVECTOR2Z[0].z = objPos.z + vec1.z;
	D3DXVECTOR2Z[1].x = objPos.x + vec2.x;
	D3DXVECTOR2Z[1].y = objPos.y + vec2.y;
	D3DXVECTOR2Z[1].z = objPos.z + vec2.z;
	D3DXVECTOR2Z[2].x = objPos.x + vec3.x;
	D3DXVECTOR2Z[2].y = objPos.y + vec3.y;
	D3DXVECTOR2Z[2].z = objPos.z + vec3.z;
	D3DXVECTOR2Z[3].x = objPos.x + vec4.x;
	D3DXVECTOR2Z[3].y = objPos.y + vec4.y;
	D3DXVECTOR2Z[3].z = objPos.z + vec4.z;
	D3DXVECTOR2Z[4].x = objPos.x + vec5.x;
	D3DXVECTOR2Z[4].y = objPos.y + vec5.y;
	D3DXVECTOR2Z[4].z = objPos.z + vec5.z;
	D3DXVECTOR2Z[5].x = objPos.x + vec6.x;
	D3DXVECTOR2Z[5].y = objPos.y + vec6.y;
	D3DXVECTOR2Z[5].z = objPos.z + vec6.z;
	D3DXVECTOR2Z[6].x = objPos.x + vec7.x;
	D3DXVECTOR2Z[6].y = objPos.y + vec7.y;
	D3DXVECTOR2Z[6].z = objPos.z + vec7.z;
	D3DXVECTOR2Z[7].x = objPos.x + vec8.x;
	D3DXVECTOR2Z[7].y = objPos.y + vec8.y;
	D3DXVECTOR2Z[7].z = objPos.z + vec8.z;
}
