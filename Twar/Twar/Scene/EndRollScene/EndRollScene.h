//==================================================================================================================================//
//!< @file		EndRollScene.h
//!< @brief		EndRollSceneクラスヘッダ
//!< @author	haga
//==================================================================================================================================//


#ifndef END_ROLL_SCENE_H
#define END_ROLL_SCENE_H

#include <d3dx9.h>

#include "../Scene.h"
/**
* エンドロールシーンのクラス
*/
class EndRollScene :public Scene
{
public:
	/**TextureID*/
	enum TEXTURE_ID
	{
		RESULT_TEX,			//!< 結果画像のTexture
		TEXT_TEX,			//!< テキスト画像のTexture
	};

	/**VertexID*/
	enum VERTEX_ID
	{
		RESULT_VTX,			//!< 結果画像のVertex
		TEXT_VTX,			//!< テキスト画像のVertex
	};

	/**コンストラクタ*/
	EndRollScene();

	/**デストラクタ*/
	~EndRollScene();

	/**コントロール関数*/
	virtual SCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	D3DXVECTOR2			m_BackgroundPos;		//!< 背景の位置座標
	D3DXVECTOR2			m_TextPos;				//!< テキストの位置座標
	int					m_DispTimeCount;		//!< 表示時間

};

#endif // END_ROLL_SCENE_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
