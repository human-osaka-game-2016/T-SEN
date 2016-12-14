/**
* @file  APBullet.cpp
* @brief APBulletクラスの実装
* @author Matsuda
*/
#include "Ap.h"
#include "GameLib/GameLib.h"

ApBullet::ApBullet()
{
	m_pFbx = m_APBullet.m_pModel;
	m_pFirst = nullptr;
	m_pLast = nullptr;
	m_Data.BulletPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Data.hasDrawn = false;
	m_Data.hasInited = false;
}

ApBullet::~ApBullet()
{
	Clear();
}

//コントロール関数
void ApBullet::Control(D3DXVECTOR3 Pos, float Rotate)
{
	float BulletSpeed = 10.f;
	float DrawRange = 1000;
	static int BulletTime = 0;
	
	Data* pData = nullptr;
	BulletTime++;
	if (GameLib::Instance().CheckKey(DIK_1, ONE) == PUSH&&BulletTime >= 120)
	{
		m_Data.hasDrawn = true;
		m_Data.hasInited = true;
		BulletTime = 0;
		if (m_Data.hasInited)
		{
			pData = new Data;
			pData->BulletPos = Pos;
			pData->BulletPos.y += 10;
			pData->Rotate = Rotate;
			PushBack(pData);
		}
	}

	pData = m_pFirst;

	while (pData)
	{
		pData->BulletPos.z += cos(3.141592 / 180 * pData->Rotate)*BulletSpeed;
		pData->BulletPos.x += sin(3.141592 / 180 * pData->Rotate)*BulletSpeed;

		if (Pos.z - pData->BulletPos.z > DrawRange || Pos.z - pData->BulletPos.z<-DrawRange ||
			Pos.x - pData->BulletPos.x>DrawRange || Pos.x - pData->BulletPos.x < -DrawRange)
		{
			m_Data.hasDrawn = false;
			m_Data.hasInited = false;
			pData = EraseNext(pData);
		}
		else
		{
			pData = pData->pNext;
		}
	}
}

//描画関数
void ApBullet::Draw()
{
	if (m_Data.hasDrawn)
	{

		D3DXMATRIX      matWorld;						// ワールド座標
		Data* pData = m_pFirst;
		while (pData)
		{
			D3DXMatrixIdentity(&matWorld);  				// 単位行列
			D3DXMatrixTranslation(&pData->Matrix, pData->BulletPos.x, pData->BulletPos.y, pData->BulletPos.z);
			D3DXMatrixMultiply(&matWorld, &matWorld, &pData->Matrix);
			GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
			m_pFbx->DrawFbx();
			pData = pData->pNext;
		}

	}
}

//最後尾につける
void ApBullet::PushBack(Data* pdata)
{
	if (!m_pFirst)
	{
		m_pFirst = pdata;
	}
	if (m_pLast)
	{
		m_pLast->pNext = pdata;
	}
	pdata->pBefore = m_pLast;
	pdata->pNext = nullptr;
	m_pLast = pdata;
}

//次のポインターを渡す
ApBullet::Data * ApBullet::EraseNext(Data* pdata)
{
	Data* pReturn = pdata->pNext;
	if (pdata->pBefore)
	{
		pdata->pBefore->pNext = pReturn;
	}
	else
	{
		m_pFirst = pReturn;
	}
	if (pReturn)
	{
		pReturn->pBefore = pdata->pBefore;
	}
	else
	{
		m_pLast = pdata->pBefore;
	}
	delete pdata;
	return pReturn;
}

//リストを空にする
void ApBullet::Clear()
{
	Data* pData;
	Data* pNext;
	pNext = m_pFirst;

	while (pNext)
	{
		pData = pNext;
		pNext = pData->pNext;
		delete pData;
	}
	m_pFirst = m_pLast = nullptr;
}
