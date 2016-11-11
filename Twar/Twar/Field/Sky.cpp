/**
* @file  Sky.cpp
* @brief Skyクラス実装
* @author Matsuda
*/
#include"Sky.h"
#include"GameLib/GameLib.h"
#include"GameLib/Lib/XFile.h"

Sky::Sky()
	:m_Pos(0,0,0)
	,m_Scale(4000)
{
	GameLib::GetInstance().LoadXFile(2, TEXT("../Resouce\\Sky.x"));
}

Sky::~Sky()
{

}

void Sky::Control()
{

}

void Sky::Draw()
{
	GameLib::GetInstance().SetFVF(USER_VERTEX_FVF);
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXMATRIX		matPos;							// 移動用行列
	D3DXMATRIX      matScale;
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXMatrixTranslation(&matPos, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&matScale, m_Scale, m_Scale, m_Scale);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matScale);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	GameLib::GetInstance().GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	GameLib::GetInstance().DrawXFile(2);
}
