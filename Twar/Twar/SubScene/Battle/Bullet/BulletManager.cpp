/**
* @file  BulletManager.cpp
* @brief BulletManagerƒNƒ‰ƒX‚ÌŽÀ‘•
* @author Matsuda
*/
#include "Ap.h"
#include "BulletManager.h"

BulletManager::BulletManager()
	: m_pAPBulletModel(new FbxRelated())
	, m_BulletCount(0)
{
	m_pAPBulletModel->LoadFbx("fbx/tama_0.FBX");

	m_BulletSize.m_MaxX = m_pAPBulletModel->m_pModel->maxX;
	m_BulletSize.m_MaxY = m_pAPBulletModel->m_pModel->maxY;
	m_BulletSize.m_MaxZ = m_pAPBulletModel->m_pModel->maxZ;
	m_BulletSize.m_MinX = m_pAPBulletModel->m_pModel->minX;
	m_BulletSize.m_MinY = m_pAPBulletModel->m_pModel->minY;
	m_BulletSize.m_MinZ = m_pAPBulletModel->m_pModel->minZ;
	m_BulletSize.m_MaxR = m_pAPBulletModel->m_pModel->maxR;
}

BulletManager::~BulletManager()
{
	for (auto pBullet : m_pBullet)
	{
		delete pBullet;
	}

	delete m_pAPBulletModel;
}

void BulletManager::Control(D3DXVECTOR3 Pos, float Rotate)
{
	//for (char i = 0; i < m_BulletCount; i++)
	//{
	//	m_pBullet[i]->Control(Pos, Rotate);
	//}

	for (auto& itr = m_pBullet.begin(); itr != m_pBullet.end();)
	{
		if ((*itr)->Control())
		{
			delete (*itr);
			itr = m_pBullet.erase(itr);
			continue;
		}
		++itr;
	}
}

void BulletManager::Draw()
{
	//for (char i = 0; i < m_BulletCount; i++)
	//{
	//	m_pBullet[i]->Draw();
	//}
	for (auto& itr = m_pBullet.begin(); itr != m_pBullet.end();)
	{
		(*itr)->Draw();
		++itr;
	}
}

void BulletManager::Create(const D3DXVECTOR3& rPos, float angle, D3DXVECTOR3* vec)
{
	m_pBullet.push_back(new ApBullet(m_pAPBulletModel->m_pModel, rPos, angle, vec));


	//m_BulletCount = *pCount;
	//for (char i = 0; i < m_BulletCount; i++)
	//{
	//	Bullet* pbullet = nullptr;
	//
	//	switch (pBulletID[i])
	//	{
	//	case APBULLET:
	//		pbullet = new ApBullet();
	//		pbullet->m_pFbx = m_pAPBulletModel->m_pModel;
	//		break;
	//	}
	//	m_Bullet.push_back(pbullet);
	//}
}

