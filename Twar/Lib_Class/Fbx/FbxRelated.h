/**
* @file FbxRelated.h
* @brief Fbxモデルのデータを読み込むクラスのh
* @author 川口
*/

#ifndef FBXRELATED_H
#define FBXRELATED_H

#include "FbxModel.h"


class FbxRelated
{
	friend class FbxModel;

private:
	fbxsdk::FbxManager*		m_pFbxManager;
	fbxsdk::FbxScene*		m_pFbxScene;

	void TriangulateRecursive(FbxNode* pNode, FbxScene* pScene);						//!<	三角形化関数
	bool InitializeFbxSdkObjects();														//!<	Fbxの初期化関数
	void GetMesh(fbxsdk::FbxNode* pNode);												//!<	メッシュ取得関数
	void GetPosition(fbxsdk::FbxMesh* pMesh);											//!<	頂点座標取得関数
	void GetVertexNormal(fbxsdk::FbxMesh* pMesh);										//!<	法線取得関数
	void GetVertexUV(fbxsdk::FbxMesh* pMesh);											//!<	UV取得関数
	void GetMaterialData(fbxsdk::FbxMesh* pMesh);										//!<	マテリアルとテクスチャ名取得関数
	void GetTextureName(fbxsdk::FbxSurfaceMaterial* pMaterial, const char* pMatAttr);	//!<	テクスチャ名取得関数
//	void GetVertexColor(fbxsdk::FbxMesh* pMesh);										//!<	頂点カラー取得関数	未使用

public:
	FbxRelated();
	~FbxRelated();																		
	void Release();																		//!<	解放関数

	/**
	* モデルデータの読み込み関数
	* @param[in] pName    Fbxファイルへのパス
	* @retval true		モデル読み込み成功
	* @retval false		モデル読み込み失敗
	*/
	bool LoadFbx(const char* pName);
	
	FbxModel* m_pModel;																	//!<	モデルデータを格納する場所
};

#endif //	FBXRALATED_H