/**
* @file  APBullet.cpp
* @brief APBulletクラスの実装
* @author Matsuda
*/
#include "Ap.h"
#include "GameLib/GameLib.h"

namespace
{

	const float		BulletSpeed = 8.f;				// 弾の速度
	const float		Gravity = -0.25f;				// 重力
	const float		PosYMinLimit = -10.f;			// Y軸における位置座標の最小の限界値

}

ApBullet::ApBullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float angle, D3DXVECTOR3* vec)
	: Bullet(pModel, rPos, angle, vec, BulletSpeed)
{
	//m_pFbx = m_APBullet.m_pModel;
	//m_pFirst = nullptr;
	//m_pLast = nullptr;
	//m_Data.BulletPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	//m_Data.hasDrawn = false;
	//m_Data.hasInited = false;
	//LPD3DXMESH m_pMesh = nullptr;

	//m_BulletSpeedX = static_cast<float>(sin(m_Radian) * BulletSpeed);
	//m_BulletSpeedZ = static_cast<float>(cos(m_Radian) * BulletSpeed);
	//m_BulletSpeedY = BulletSpeed / 2.f;
}

ApBullet::~ApBullet()
{
//	Clear();
	if(m_pMesh != nullptr)
	{
		m_pMesh->Release();
	}
}

//コントロール関数
bool ApBullet::Control()
{
	///*初期化*/
	//float BulletSpeed = 10.f;
	//float DrawRange = 1000;
	//static int BulletTime = 0;
	//const float Gravity = 19.8f;
	//m_Data.hasDrawn = true;
	//Data* pData = nullptr;
	//BulletTime++;
	//
	///*発射処理*/
	//if (GameLib::Instance().CheckKey(DIK_1, ONE) == PUSH && BulletTime >= 120)
	//{
	//	m_Data.FireCount = 0;
	//	m_Data.hasInited = true;
	//	BulletTime = 0;
	//	if (m_Data.hasInited)
	//	{
	//		pData = new Data;
	//		pData->BulletPos = Pos;
	//		pData->BulletPos.y += 50;
	//		pData->Rotate = Rotate;
	//		PushBack(pData);
	//	}
	//}
	//
	//pData = m_pFirst;
	//
	///*弾の移動処理*/
	//while (pData)
	//{
	//	pData->BulletOldPos = pData->BulletPos;
	//	pData->BulletPos.z += cos(3.141592f / 180.f * pData->Rotate)*BulletSpeed;
	//	pData->BulletPos.x += sin(3.141592f / 180.f * pData->Rotate)*BulletSpeed;
	//	//pData->BulletPos.y += Gravity/2;
	//
	//	//if (Pos.z - pData->BulletPos.z > DrawRange || Pos.z - pData->BulletPos.z<-DrawRange ||
	//	//	Pos.x - pData->BulletPos.x>DrawRange || Pos.x - pData->BulletPos.x < -DrawRange)
	//	//{
	//	//	pData->BulletPos.y -= Gravity;
	//	//}
	//
	//	if (pData->IsHit && pData->FireCount >= 10)
	//	{
	//		m_EffectManager.Create(pData->BulletPos, m_EffectManager.EXPLOSION);
	//		m_Data.hasDrawn = false;
	//		m_Data.hasInited = false;
	//		m_Data.IsHit = false;
	//		pData = EraseNext(pData);
	//	}
	//	else if (pData->BulletPos.y <= 0)
	//	{
	//		m_Data.hasDrawn = false;
	//		m_Data.hasInited = false;
	//		pData = EraseNext(pData);
	//	}
	//	else
	//	{
	//		pData = pData->pNext;
	//	}
	//	m_Data.IsHit = false;
	//	m_Data.FireCount++;
	//
	//}
	if (m_IsHit && m_FireCount >= 20)
	{
		m_HasVanished = true;
		m_IsHit = false;
		m_EffectManager.Create(m_Pos, m_EffectManager.EXPLOSION);
	}
	else if (m_FireCount < 120.f)
	{
		m_IsHit = false;
		m_OldPos = m_Pos;
		m_Pos.x += m_BulletSpeedX;
		m_Pos.z += m_BulletSpeedZ;
		m_Pos.y += m_BulletSpeedY;

		if (m_Pos.y < PosYMinLimit)
		{
			m_HasVanished = true;
		}
	}
	else if (m_FireCount >= 120)
	{
		m_IsHit = false;
		m_OldPos = m_Pos;
		m_Pos.x += m_BulletSpeedX;
		m_Pos.z += m_BulletSpeedZ;
		m_Pos.y += m_BulletSpeedY + Gravity * m_FlyingTimeCount;

		if (m_Pos.y < PosYMinLimit)
		{
			m_HasVanished = true;
		}
		m_FlyingTimeCount++;
	}
	else
	{
		m_HasVanished = true;
	}
	m_FireCount++;

	return m_HasVanished;

}

//描画関数
void ApBullet::Draw()
{
	//if (m_Data.hasDrawn)
	//{
	//	D3DXMATRIX      matWorld;						// ワールド座標
	//	Data* pData = m_pFirst;
	//	
	//	while (pData)
	//	{
	//		D3DXMatrixIdentity(&matWorld);  				// 単位行列
	//		D3DXMatrixTranslation(&pData->Matrix, pData->BulletPos.x, pData->BulletPos.y, pData->BulletPos.z);
	//		D3DXMatrixMultiply(&matWorld, &matWorld, &pData->Matrix);
	//		GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	//		m_pFbx->DrawFbx();
	//		pData = pData->pNext;
	//		D3DXCreateSphere(GameLib::Instance().GetDevice(),20,64,32,&m_pMesh,nullptr);
	//		m_pMesh->DrawSubset(0);
	//	}
	//}
	D3DXMatrixIdentity(&m_MatWorld);

	// 回転
	D3DXMATRIX			matHeading;
	D3DXMatrixRotationY(&matHeading, m_Radian);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matHeading);

	// 移動
	D3DXMATRIX			matPosition;	// 位置座標行列
	D3DXMatrixTranslation(&matPosition, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matPosition);
	GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &m_MatWorld);
	m_pFbx->DrawFbx();
}

//最後尾につける
//void ApBullet::PushBack(Data* pdata)
//{
//	if (!m_pFirst)
//	{
//		m_pFirst = pdata;
//	}
//	if (m_pLast)
//	{
//		m_pLast->pNext = pdata;
//	}
//	pdata->pBefore = m_pLast;
//	pdata->pNext = nullptr;
//	m_pLast = pdata;
//}

//次のポインターを渡す
//ApBullet::Data * ApBullet::EraseNext(Data* pdata)
//{
//	Data* pReturn = pdata->pNext;
//	if (pdata->pBefore)
//	{
//		pdata->pBefore->pNext = pReturn;
//	}
//	else
//	{
//		m_pFirst = pReturn;
//	}
//	if (pReturn)
//	{
//		pReturn->pBefore = pdata->pBefore;
//	}
//	else
//	{
//		m_pLast = pdata->pBefore;
//	}
//	delete pdata;
//	return pReturn;
//}

//リストを空にする
//void ApBullet::Clear()
//{
//	Data* pData;
//	Data* pNext;
//	pNext = m_pFirst;
//
//	while (pNext)
//	{
//		pData = pNext;
//		pNext = pData->pNext;
//		delete pData;
//	}
//	m_pFirst = m_pLast = nullptr;
//}
