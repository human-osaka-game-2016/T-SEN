/**
* @file SpeedMeter.cpp
* @brief SpeedMeterのクラス実装
* @author ichikawa
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "SpeedMeter.h"
#include "../BattleData/BattleDataManager.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//-------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

	const D3DXVECTOR2		MeterPos = { 100.f, 450.f };
	const float				MinTu = 0.37f;
	const float				MinTV = 0.3f;
	const float				SpeedLimit = 2.f;

	const float				SpeedMeter = 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

SpeedMeter::SpeedMeter(int aiconTexID, int meterVtxID, int MeaterID)
	: m_SpeedMeterPos({ 130.f, 296.f })
	, m_AiconPos({ 53.f, 596.f })
{
	m_PosY = 0.0f;
	m_Pos = MeterPos;
	m_CurrentSpeed = BattleDataManager::Instance().GetPlayerSpeed();
	m_SpeedCount = 148.f / BattleDataManager::Instance().GetSpeedLimit();
	m_Angle = 0.0f;
	m_TexID[UI] = aiconTexID;
	//m_TexID[DIAL] = dialTexID;
	//m_TexID[UI] = meterVtxID;
	m_AICON_ID = meterVtxID;
	m_SpeedMeterID = MeaterID;
	m_SpeedLimit = 120.f / SpeedLimit;
	GameLib::Instance().CreateVtx(m_AICON_ID, 33.f, 50.f);
	GameLib::Instance().CreateVtx(m_SpeedMeterID, 85.f, 296.f);
}

SpeedMeter::~SpeedMeter()
{
}

void SpeedMeter::Control()

{
	m_CurrentSpeed = BattleDataManager::Instance().GetPlayerSpeed();
	//m_Angle = m_CurrentSpeed * m_SpeedCount;

	m_PosY = m_CurrentSpeed * m_SpeedCount;

	///*========================================スピードメーターの上下をする=====================================*/
	//
	//if (GameLib::Instance().CheckKey(DIK_W, W) == ON)		//W入力でスピードメータ上昇
	//{
	//	if (m_AiconPos.y >= 429.f)
	//	{
	//		m_AiconPos.y = m_SpeedLimit;	//m_AiconPos.yが500以上だったら条件に入る
	//	}
	//
	//}
	//
	//else if (GameLib::Instance().CheckKey(DIK_W, W) == OFF && m_AiconPos.y < 596.f)		//Wが押させていない+m_AiconPos.ｙが原点より上にある場合メータを原点に戻す
	//{
	//
	//	m_AiconPos.y += m_SpeedLimit;
	//
	//}
	//if (GameLib::Instance().CheckKey(DIK_S, S) == ON)		//Sが押されている場合スピードメーターを減少させる
	//{
	//	if (m_AiconPos.y <= 716.f)		//m_AiconPos.yが700以下だったら条件に入る
	//	{
	//		m_AiconPos.y += m_SpeedLimit;
	//	}
	//}
	//else if (GameLib::Instance().CheckKey(DIK_S, S) == OFF && m_AiconPos.y > 596.f)		//Sが押させていない+m_AiconPos.ｙが原点より↓にある場合メータを原点に戻す
	//{
	//
	//	m_AiconPos.y -= m_SpeedLimit;
	//}
}

void SpeedMeter::Draw()
{
	GameLib::Instance().SetVtxUV(m_AICON_ID, 580.f / 1024.f, 613.f / 1024.f, 0.f / 512.f, 50.f / 512.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_AICON_ID, m_AiconPos.x, (m_AiconPos.y - m_PosY));
	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, speedmeter, sizeof(CUSTOMVERTEX));


	//RotationMatrix(needle);

	//for(char i = 0; i < 4; ++i)
	//{
	//	needle[i].x += m_NeedlePos.x;
	//	needle[i].y += m_NeedlePos.y;
	//}
	for (int i = 0; i < 4; i++)
	{
		aicon[i].x += m_AiconPos.x;
		aicon[i].y += m_AiconPos.y;
	}

	GameLib::Instance().SetVtxUV(m_SpeedMeterID, 0.f / 1024.f, 130.f / 1024.f, 0.f / 512.f, 296.f / 512.f);
	GameLib::Instance().DrawXY(m_TexID[UI], m_SpeedMeterID, m_Pos.x, m_Pos.y);

	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[UI]));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, aicon, sizeof(CUSTOMVERTEX));
	/*===================================================for文で座標を減加算する======================================*/


	/*================================================================================================================*/

}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//-------------------------------------------------------------------------------------------------------------------------------------//
/*=============================================新基準では不必要なのでコメントアウト====================================================
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
=======================================================================================================================================*/

/*==============================================新基準には必要ないためコメントアウト=====================================================
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

========================================================================================================================================*/