//==================================================================================================================================//
//!< @file		SpeedMeter.cpp
//!< @brief		SpeedMeterクラス実装
//!< @author	ichikawa
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "SpeedMeter.h"
#include "../BattleData/BattleDataManager.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnmaed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const D3DXVECTOR2		MeterPos = {140.f, 600.f};
const float				MinTu = 0.37f;
const float				MinTV = 0.3f;
const float				SpeedLimit = 2.f;

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

SpeedMeter::SpeedMeter(int bgTexID, int dialTexID, int needleTexID, int meterVtxID)
	: m_NeedlePos({344.f, 900.f})
{
	m_Pos = MeterPos;
	//m_CurrentSpeed = BattleStateManager::Instance().GetShipSpeed();
	m_SpeedCount = 85.f / SpeedLimit;
	m_Angle = 0.0f;
	m_TexID[BG] = bgTexID;
	m_TexID[DIAL] = dialTexID;
	m_TexID[NEEDLE] = needleTexID;
	m_VtxID = meterVtxID;
	GameLib::Instance().CreateVtx(m_VtxID, 600.f, 300.f);
}

SpeedMeter::~SpeedMeter()
{
}

void SpeedMeter::Control()
{
	//m_CurrentSpeed = BattleStateManager::Instance().GetShipSpeed();
	m_Angle = m_CurrentSpeed * m_SpeedCount;

}

void SpeedMeter::Draw()
{

	GameLib::Instance().DrawXY(m_TexID[BG], m_VtxID,  m_Pos.x, m_Pos.y);
	GameLib::Instance().DrawXY(m_TexID[DIAL], m_VtxID, m_Pos.x, m_Pos.y);

	CUSTOMVERTEX needle[] =
	{
		{ -200.f, -200.f, 0.0f, 1.0f, 0xFFFFFFFF, MinTu, MinTV },
		{ 200.f, -200.f, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, MinTV },
		{  200.f,    0.f, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
		{ -200.f,	 0.f, 0.0f, 1.0f, 0xFFFFFFFF, MinTu, 1.0f },
	};

	RotationMatrix(needle);

	for(char i = 0; i < 4; ++i)
	{
		needle[i].x += m_NeedlePos.x;
		needle[i].y += m_NeedlePos.y;
	}

	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[NEEDLE]));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, needle, sizeof(CUSTOMVERTEX));
}

//--------------------------------------------------------------------------------------------------------------//
//Priavte functions
//--------------------------------------------------------------------------------------------------------------//

//行列を使用した回転関数（+だと右回転、-だと左回転)
void  SpeedMeter::RotationMatrix(CUSTOMVERTEX* vertex)
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
	for(int i = 0; i<4; i++)
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

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
