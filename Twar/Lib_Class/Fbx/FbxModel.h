/**
* @file		FbxModel.h
* @brief	FbxModelクラスヘッダ
* @author	kawaguchi
*/

#ifndef FBXMODEL_H
#define FBXMODEL_H

#include <fbxsdk.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <list>
#include <vector>
#include "../GameLib/Lib/GraphicsDevice.h"

#define MY_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2)

/**
* Fbxモデルのデータを詰めるクラス
*/
class FbxModel
{
	friend class FbxRelated;

private:
	typedef struct VERTEX
	{
		D3DXVECTOR3  Vec;					//!< 頂点データ
		D3DXVECTOR3  Normal;				//!< 法線ベクトル
		float tu;
		float tv;
	}Vertex;

	typedef struct COLOR_RGBAF
	{
		float r;
		float g;
		float b;
		float a;
	}ColorRGBA;

	typedef struct UV_SET
	{
		std::string uvSetName;
		std::vector<D3DXVECTOR2*> uvBuffer;
	}UvSet;

	typedef struct TEXTURE_DATA
	{
		LPCSTR TextureName;
		LPDIRECT3DTEXTURE9 pTexture;
	}TextureData;

	typedef struct FBXMODELDATA
	{
		int polygonCount = 0;						//!<	ポリゴン数
		int vertexCount = 0;						//!<	総頂点数（コントロールポイント）
		int indexCount = 0;							//!<	インデックス数（）
		int fileTextureCount = 0;					//!<	テクスチャ数
		int materialCount = 0;						//!<	マテリアル数
		int UvLayerCount = 0;						//!<	UVレイヤーテクスチャ数
		int uvIndexCount = 0;						//!<	UVのインデックス数

		int* pIndexBuffer = NULL;					//!<	インデックスバッファ
		int* pPolygonSize = NULL;					//!<	ポリゴン数

		Vertex* pVertex = NULL;						//!<	頂点座標
		ColorRGBA* pVertexColor = NULL;				//!<	頂点カラー
		UvSet uvSet;								//!<	UV情報
		TextureData* pTmpTexture;					//!<	ネームの仮置き場
		std::vector<TextureData*> pTextureData;		//!<	テクスチャデータ
		std::vector<D3DMATERIAL9> MaterialData;		//!<	マテリアルデータ

}FbxModelData;

	FbxModelData* m_pFbxModelData;					//!<	全モデルデータ
	IDirect3DDevice9*			m_pDevice;			//!<	Direct3Dのデバイス

public:
	FbxModel();
	~FbxModel();
	void DrawFbx();
};

#endif	//	FBXMODEL_H
