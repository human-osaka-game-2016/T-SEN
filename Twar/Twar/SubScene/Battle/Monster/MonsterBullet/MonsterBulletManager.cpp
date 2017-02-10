/**
* @file		MonsterBulletManager.cpp
* @brief	MonsterBulletManagerクラス実装
* @author	haga
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "Fbx/FbxRelated.h"
#include "MonsterBulletManager.h"
#include "MonsterBullet.h"
#include "LongRangeBullet.h"
#include "ShortRangeBullet.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//--------------------------------------------------------------------------------------------------------------------------------------//

// 値は仮置き
namespace
{

const int		FiredBulletNum = 50;				// 近距離弾の発射回数
const float		FiringRadian = 0.1256f;				// 近距離弾の発射方向(ラジアンを格納するため、変数名はradian)

}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

MonsterBulletManager::MonsterBulletManager()
	: m_pLongRangeBulletModel(new FbxRelated())
	, m_pShortRangeBulletModel(new FbxRelated())
{
	// モデルデータ読み込み
	/**@todo 2016/12/23現在モデルデータは仮置き*/
	if(!m_pLongRangeBulletModel->LoadFbx("fbx/ganseki.FBX"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "遠距離弾のFBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}

	if(!m_pShortRangeBulletModel->LoadFbx("fbx/ganseki.FBX"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "近距離弾のFBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}

	m_MonsterBulletSize.m_MaxX = m_pLongRangeBulletModel->m_pModel->maxX;
	m_MonsterBulletSize.m_MaxY = m_pLongRangeBulletModel->m_pModel->maxY;
	m_MonsterBulletSize.m_MaxZ = m_pLongRangeBulletModel->m_pModel->maxZ;
	m_MonsterBulletSize.m_MinX = m_pLongRangeBulletModel->m_pModel->minX;
	m_MonsterBulletSize.m_MinY = m_pLongRangeBulletModel->m_pModel->minY;
	m_MonsterBulletSize.m_MinZ = m_pLongRangeBulletModel->m_pModel->minZ;
	m_MonsterBulletSize.m_MaxR = m_pLongRangeBulletModel->m_pModel->maxR;

}

MonsterBulletManager::~MonsterBulletManager()
{
	for(auto pBullet : m_pBullets)
	{
		delete pBullet;
	}

	delete m_pShortRangeBulletModel;
	delete m_pLongRangeBulletModel;
}

// コントロール関数
void MonsterBulletManager::Control()
{
	for(auto itr = m_pBullets.begin(); itr != m_pBullets.end();)
	{
		if((*itr)->Control())
		{
			delete (*itr);
			itr = m_pBullets.erase(itr);
			continue;
		}
		++itr;
	}
}

// 描画関数
void MonsterBulletManager::Draw()
{
	for(auto itr = m_pBullets.begin(); itr != m_pBullets.end();)
	{
		(*itr)->Draw();
		++itr;
	}
}

// 遠距離弾を生成する関数
void MonsterBulletManager::CreateLongeRangeBullet(const D3DXVECTOR3& rPos, float radian)
{
	m_pBullets.push_back(new LongRangeBullet(m_pLongRangeBulletModel->m_pModel, rPos, radian));
}

// 近距離弾を生成する関数
void MonsterBulletManager::CreateShortRangeBullet(const D3DXVECTOR3& rPos)
{
	float firingRadian = 0.0f;

	for(int i = 0; i < FiredBulletNum; ++i)
	{
		firingRadian += (FiringRadian * i);

		// 一方向に3発発射する(処理が重くなったら減らす)
		m_pBullets.push_back(new ShortRangeBullet(m_pLongRangeBulletModel->m_pModel, rPos, firingRadian));
		m_pBullets.push_back(new ShortRangeBullet(m_pLongRangeBulletModel->m_pModel, rPos, firingRadian));
		m_pBullets.push_back(new ShortRangeBullet(m_pLongRangeBulletModel->m_pModel, rPos, firingRadian));
	}
}
