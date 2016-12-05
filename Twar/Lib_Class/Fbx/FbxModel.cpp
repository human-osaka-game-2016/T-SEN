/**
* @file		FbxModel.cpp
* @brief	FbxModelクラス実装
* @author	kawaguchi
*/

#include "FbxModel.h"

FbxModel::FbxModel()
	: m_pDevice(GraphicsDevice::GetInstance().GetDevice())
{
	m_pFbxModelData= NULL;
}

FbxModel::~FbxModel()
{
}

void FbxModel::DrawFbx()
{
	m_pDevice->SetFVF(MY_FVF);
	
	for (int i = 0; i < m_pFbxModelData->materialCount; i++)
	{
		m_pDevice->SetMaterial(&m_pFbxModelData->MaterialData[i]);
	}

	for (unsigned int n = 0; n < m_pFbxModelData->pTextureData.size(); n++)
	{
		m_pDevice->SetTexture(n, m_pFbxModelData->pTextureData[n]->pTexture);
	}

	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_pFbxModelData->polygonCount,
		m_pFbxModelData->pVertex,
		sizeof(Vertex));
}
