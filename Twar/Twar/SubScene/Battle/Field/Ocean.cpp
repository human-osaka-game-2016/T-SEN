/**
* @file  Ocean.cpp
* @brief Oceanクラス実装
* @author Matsuda
*/
#include"Ocean.h"
#include"GameLib/GameLib.h"

Ocean::Ocean()
	: m_Pos(0.0f, 2.0f, 0.0f)
	, m_Scale(1.0f)
{
	GameLib::Instance().LoadXFile(1, "../Resouce/BattleScene/Xfile/sea.x");
}

Ocean::~Ocean()
{

}

void Ocean::Control()
{

}

void Ocean::Draw()
{
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXMATRIX		matPos;							// 移動用行列
	D3DXMATRIX      matScale;
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXMatrixTranslation(&matPos, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&matScale, m_Scale, m_Scale, m_Scale);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matScale);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	GameLib::Instance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	GameLib::Instance().DrawXFile(1);
}
