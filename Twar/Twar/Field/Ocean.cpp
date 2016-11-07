#include"Ocene.h"

Ocene::Ocene():
m_pD3Device(GraphicsDevice::GetInstance().GetDevice()),
m_Pos(),
m_Scale()
{
	m_xFile.LoadXFile(TEXT("sea.x"));
}

Ocene::~Ocene()
{

}

void Ocene::Control()
{

}

void Ocene::Draw()
{
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXMATRIX		matPos;							// 移動用行列
	D3DXMATRIX      matScale;
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXMatrixTranslation(&matPos, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&matScale, m_Scale, m_Scale, m_Scale);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matScale);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);
	m_xFile.DrawX();
}