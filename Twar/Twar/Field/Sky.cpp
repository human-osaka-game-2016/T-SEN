/**
* @file  Sky.cpp
* @brief Skyクラス実装
* @author Matsuda
*/
#include"Sky.h"
#include"GameLib/GameLib.h"
#include"GameLib/Lib/XFile.h"

Sky::Sky()
	: m_pXFile(new XFile())
	, m_Pos(0.0f, 0.0f, 0.0f)
	, m_Scale(0.0f)
{
	m_pXFile->LoadXFile(TEXT("Sky.x"));
}

Sky::~Sky()
{

}

void Sky::Control()
{

}

void Sky::Draw()
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
	m_pXFile->DrawX();
}
