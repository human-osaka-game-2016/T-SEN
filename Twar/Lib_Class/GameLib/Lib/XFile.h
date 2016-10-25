/**
* @file   XFile.h
* @brief  Xファイルを扱うクラスのh
* @author haga
*/
#ifndef XFILE_H
#define XFILE_H

#include "GraphicsDevice.h"

/**
* Xファイルを扱うクラス
*/
class XFile
{
private:
	IDirect3DDevice9*		m_pD3Device;		//!< Direct3Dのデバイス
	LPD3DXMESH				m_pMesh;			//!< ID3DXMeshのインターフェイスへのポインタ
	D3DMATERIAL9*			m_pMaterials;		//!< マテリアル
	LPDIRECT3DTEXTURE9*		m_pTextures;		//!< テクスチャー
	DWORD					m_dwNumMaterials;	//!< マテリアル数

public:
	/**コンストラクタ*/
	XFile();

	/**デストラクタ*/
	~XFile();

	/**
	* Xファイルからデータを読み込む関数.
	* @param[in] pFilename ファイル名
	* @retval	true	読み込み成功
	* @retval	false	読み込み失敗
	*/
	bool LoadXFile(LPCTSTR pFilename);

	/**
	* メッシュを描画する関数.
	*/
	void DrawX();

	/**
	* メモリ解放関数<br>
	* FailManagerに使用するために作成
	*/
	void Release();
};

#endif	// XFILE_H