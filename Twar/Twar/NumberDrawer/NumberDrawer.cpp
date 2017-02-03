//==================================================================================================================================//
//!< @file		NumberDrawer.cpp
//!< @brief		NumberDrawerクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "NumberDrawer.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const	float		TextureWidth = 2048.f;		// テクスチャーの横幅
const	float		TextureHeight = 2048.f;		// テクスチャーの縦幅
const   float		NumberWidthSize = 44.f;		// 番号の横幅
const   float		NumberHeightSize = 60.f;	// 番号の縦幅
const	float		StartTexturePosX = 1080.f;	// テクスチャーにおける番号の開始X軸の位置座標
const	float		StartTexturePosY = 330.f;	// テクスチャーにおける番号の開始Y軸の位置座標

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

NumberDrawer::NumberDrawer(int texID, int vtxID)
	: m_TexID(texID)
	, m_VtxID(vtxID)
{
	// Textureの読み込みとVertexの作成は別で行う
}

NumberDrawer::~NumberDrawer()
{
	// リソース解放は別で行う
}

void NumberDrawer::Draw(const D3DXVECTOR2 rPos, int num)
{
	float minTu = (StartTexturePosX + NumberWidthSize * num) / TextureWidth;
	float maxTu = (StartTexturePosX + NumberWidthSize * (num + 1)) / TextureWidth;
	float minTv = StartTexturePosY / TextureHeight;
	float maxTv = (StartTexturePosY + NumberHeightSize ) / TextureHeight;

	GameLib::Instance().SetVtxUV(m_VtxID, minTu, maxTu, minTv, maxTv);
	GameLib::Instance().DrawXY(m_TexID, m_VtxID, rPos.x, rPos.y);
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
