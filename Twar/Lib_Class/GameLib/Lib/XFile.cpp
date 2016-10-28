/**
* @file   XFile.cpp
* @brief  Xファイルを扱うクラスのcpp
* @author haga
*/

#include "XFile.h"

// コンストラクタ
XFile::XFile() :m_pD3Device(GraphicsDevice::GetInstance().GetDevice()),
m_pMesh(NULL),
m_pMaterials(NULL),
m_pTextures(NULL),
m_dwNumMaterials(0)
{
}

// デストラクタ
XFile::~XFile()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	delete[] m_pMaterials;
	delete[] m_pTextures;
}

// Xファイルからデータを読み込む関数
bool XFile::LoadXFile(LPCTSTR pFilename)
{
	// メッシュをロードする
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL; // マテリアル情報を格納するデータバッファ

	if (FAILED(D3DXLoadMeshFromX(
		pFilename,					// ファイル名
		D3DXMESH_SYSTEMMEM,			// メッシュ作成オプション
		m_pD3Device,
		NULL,						// 隣接性データを含むバッファへのポインタ
		&pD3DXMtrlBuffer,
		NULL,						// 返されるメッシュ内の属性グループごとに 1 つの、エフェクト インスタンスの配列を含むバッファへのポインタ
		&m_dwNumMaterials, 
		&m_pMesh)))
	{
		MessageBox(NULL,"Xファイルの読み込みに失敗しました",NULL,MB_OK);
		return false;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();		// マテリアル・バッファへのポインタを宣言、初期化
	m_pMaterials = new D3DMATERIAL9[m_dwNumMaterials];										// マテリアルのメモリをマテリアルの数分だけ確保する
	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];									// テクスチャーのメモリをマテリアルの数分だけ確保する

	// m_pMaterialsとm_pTexturesの中身が空なのでマテリアルデータを代入する
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		m_pMaterials[i] = d3dxMaterials[i].MatD3D;
		 m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;
		 m_pTextures[i] = NULL;
		 if (d3dxMaterials[i].pTextureFilename != NULL &&
			 lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		 {
			 if (FAILED(D3DXCreateTextureFromFile(
				 m_pD3Device,
				 d3dxMaterials[i].pTextureFilename,
				 &m_pTextures[i])))
			 {
				 MessageBox(0, "テクスチャの読み込みに失敗しました。", NULL, MB_OK);
			 }
		 }
	}

	pD3DXMtrlBuffer->Release();		// 不要なのでメモリを開放する

	return true;
}

// 描画関数
void XFile::DrawX()
{
	for (DWORD i = 0; i < m_dwNumMaterials;i++)
	{
		m_pD3Device->SetMaterial(&m_pMaterials[i]);
		m_pD3Device->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}

// メモリ解放
void XFile::Release()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	delete m_pMaterials;
	delete m_pTextures;
}