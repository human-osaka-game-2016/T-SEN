/**
* @file  BulletManager.cpp
* @brief BulletManagerƒNƒ‰ƒX‚ÌŽÀ‘•
* @author Matsuda
*/
#include "Ap.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
	m_APBullet.LoadFbx("fbx/tama_0.FBX");
}

BulletManager::~BulletManager()
{
	for (char i = 0; i < m_BulletCount; i++)
	{
		delete m_Bullet[i];
	}
}

void BulletManager::Control(D3DXVECTOR3 Pos, float Rotate)
{
	for (char i = 0; i < m_BulletCount; i++)
	{
		m_Bullet[i]->Control(Pos, Rotate);
	}
}

void BulletManager::Draw()
{
	for (char i = 0; i < m_BulletCount; i++)
	{
		m_Bullet[i]->Draw();
	}
}

void BulletManager::Create(char* pCount,BULLET_ID* pBulletID)
{
	m_BulletCount = *pCount;
	for (char i = 0; i < m_BulletCount; i++)
	{
		Bullet* pbullet = nullptr;

		switch (pBulletID[i])
		{
		case APBULLET:
			pbullet = new ApBullet();
			pbullet->m_pFbx = m_APBullet.m_pModel;
			break;
		}
		m_Bullet.push_back(pbullet);
	}
}

