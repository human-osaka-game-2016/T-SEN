/**
* @file MnsterLifeGauge.cpp
* @brief MnsterLifeGaugeのクラス実装
* @author ichikawa
*/

//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "MonsterLifeGauge.h"
#include "../BattleData/BattleDataManager.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

	const float			LifePosX = 1115.f;
	const D3DXVECTOR2	Pos = { 1115.f, 40.f };
	const float			VtxHeight = 100.f;
	const float			VtxWidth = 450.f;

}

//--------------------------------------------------------------------------------------------------------------------------------------//
//public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

MonsterLifeGauge::MonsterLifeGauge(int lifeTexID, int LifeVtrID, int FlameVtrID)
	: m_LifeTv(0.0f)
	, m_LifeTu(130.f / 1024.f)
	, m_LifeHeight(100.f)
	, m_LifeWide(450.f)
{
	m_Angle = 90.f;
	m_LifeMAX = BattleDataManager::Instance().GetMonsterHp();
	m_CurrentLife = m_LifeMAX;
	m_LifeTvCount = 1.0f / m_LifeMAX;
	m_LifePos = Pos;
	m_LifeFlamePos = Pos;
	m_LifePosCount = VtxWidth / m_LifeMAX;
	m_Pos = Pos;

	m_TexID[UI] = lifeTexID;
	m_LifeFlameID = FlameVtrID;
	GameLib::Instance().CreateVtx(m_LifeFlameID, 450.f, 100.f);
	m_LifeID = LifeVtrID;
	GameLib::Instance().CreateVtx(m_LifeID, 450.f, 100.f);
	m_LifeBaseID = FlameVtrID;
	GameLib::Instance().CreateVtx(m_LifeBaseID, 450.f, 100.f);
}

MonsterLifeGauge::~MonsterLifeGauge()
{
}

void MonsterLifeGauge::Control()
{
	m_CurrentLife = BattleDataManager::Instance().GetMonsterHp();

	//if (m_LifeMAX != m_CurrentLife)
	//{
	//
	//	m_LifeTu += (m_LifeMAX - m_CurrentLife) * m_LifeTvCount;	//ダメージ表示分
	//	m_LifePos.x += ((m_LifeMAX - m_CurrentLife) * m_LifePosCount) / 1.0f;	//ダメージ表示分
	//	m_LifeWide -= (m_LifeMAX - m_CurrentLife) * m_LifePosCount;;	//ダメージ計算
	//	m_LifeMAX = m_CurrentLife;
	//
	//}


	//if (m_LifeMAX != m_CurrentLife)
	//{
	//	m_CurrentLife -= 2;
	//	m_LifeTu -= (m_LifeMAX - m_CurrentLife) * m_LifeTvCount;
	//	m_LifePos.x += ((m_LifeMAX - m_CurrentLife) * m_LifePosCount) / 1.0f;
	//	m_LifeWide -= (m_LifeMAX - m_CurrentLife) * m_LifePosCount;
	//	m_LifeMAX = m_CurrentLife;
	//}
}

void MonsterLifeGauge::Draw()
{
	// 下地
	//GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	//GameLib::Instance().SetVtxUV(m_LifeBaseID, 0.f / 1024.f, (0.f + VtxWidth) / 1024.f, 300.f / 512.f, (300.f + VtxHeight) / 512.f);
	//GameLib::Instance().DrawXY(m_TexID[UI], m_LifeBaseID, m_LifeFlamePos.x, m_LifeFlamePos.y);

	/*CUSTOMVERTEX life[] =
	{
	{ -VtxWidth / 2.0f, -m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 0.0f, m_LifeTv },
	{ VtxWidth / 2.0f, -m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 1.0f, m_LifeTv },
	{ VtxWidth / 2.0f, m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 1.0f, 1.0f },
	{ -VtxWidth / 2.0f, m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 0.0f, 1.0f },
	};

	for(char i = 0; i < 4; ++i)
	{
	life[i].x += m_LifePos.x;
	life[i].y += m_LifePos.y;
	}*/

	//m_LifeFlameID, 130.f / 1024.f, (130.f + VtxWidth) / 1024.f, 200.f / 512.f, (200.f + VtxHeight) / 512.f)

	// ライフゲージ
	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().SetVtxUV(m_LifeID, m_LifeTu, (130.f + VtxWidth) / 1024.f, 100.f / 512.f, (100.f + VtxHeight) / 512.f);
	//GameLib::Instance().SetVtxSize(m_LifeID, m_LifeWide, m_LifeHeight);
	GameLib::Instance().DrawXY(m_TexID[UI], m_LifeID, m_LifePos.x, m_LifePos.y);

	// フレーム描画
	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().SetVtxUV(m_LifeFlameID, 130.f / 1024.f, 580.f / 1024.f, 200.f / 512.f, 300.f / 512.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_LifeFlameID, m_LifeFlamePos.x, m_LifeFlamePos.y);

	//RotationMatrix(life);
}

/*
//---------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//---------------------------------------------------------------------------------------------------------------------------------------//

//行列を使用した回転関数（+だと右回転、-だと左回転)
void  MonsterLifeGauge::RotationMatrix(CUSTOMVERTEX* vertex)
{
D3DXMATRIX PosMatrix;		// 頂点行列
D3DXMATRIX RotateMatrix;	// 回転行列

float cx = 0.0f;		//中心座標のx座標を格納する変数
float cy = 0.0f;		//変形したy座標を一時的に保持するための変数

//画像の中心座標を求める
cx = (vertex[2].x - vertex[0].x) / 2.0f + vertex[0].x;
cy = (vertex[2].y - vertex[0].y) / 2.0f + vertex[0].y;

// 行列の初期化（単位行列生成）
D3DXMatrixIdentity(&PosMatrix);
D3DXMatrixIdentity(&RotateMatrix);

D3DXMatrixRotationZ(&RotateMatrix, D3DXToRadian(m_Angle));

// 回転処理
for (int i = 0; i < 4; i++)
{
// 現在の頂点座標を格納
D3DXMatrixTranslation(&PosMatrix, vertex[i].x, vertex[i].y, vertex[i].z);
// 回転
PosMatrix *= RotateMatrix;
// 結果を戻す
vertex[i].x = PosMatrix._41;
vertex[i].y = PosMatrix._42;
vertex[i].z = PosMatrix._43;
}
}
*/