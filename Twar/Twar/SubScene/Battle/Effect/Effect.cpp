/**
* @file		Effect.cpp
* @brief	Effectクラス実装
* @author	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "Effect.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

Effect::Effect(D3DXVECTOR3 pos, int texID, int vtxID)
	: m_Pos(pos)
	, m_TexID(texID)
	, m_VtxID(vtxID)
	, m_AnimeTimeCount(0)
	, m_AnimePatternCount(0)
	, m_IsEnd(false)
{
}

Effect::~Effect()
{
}

//--------------------------------------------------------------------------------------------------------------------------------------//
//Protected functions
//--------------------------------------------------------------------------------------------------------------------------------------//

// 座標を3D空間に変換する関数
void Effect::Transform3D()
{
	D3DXMATRIX matPosition;							// 位置座標行列
	D3DXMatrixIdentity(&m_MatWorld);
	D3DXMatrixTranslation(&matPosition, m_Pos.x, m_Pos.y, m_Pos.z);
	TransformBillboard();							// ビルボード変換
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matPosition);
	GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &m_MatWorld);
}

// ビルボード処理を行う関数
void Effect::TransformBillboard()
{
	D3DXMATRIX matCuurentView;		// 現在のビュー行列を格納する変数
	GameLib::Instance().GetDevice()->GetTransform(D3DTS_VIEW, &matCuurentView);
	D3DXMatrixInverse(&matCuurentView, NULL, &matCuurentView);			// 逆行列作成
	matCuurentView._41 = 0.0f;
	matCuurentView._42 = 0.0f;
	matCuurentView._43 = 0.0f;
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matCuurentView);
}

