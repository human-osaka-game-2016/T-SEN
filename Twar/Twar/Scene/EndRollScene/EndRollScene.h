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
		RESULT_BG_TEX,				//!< 結果背景画像のTexture
		RESULT_TEXT_TEX,			//!< 結果テキスト画像のTexture
		END_ROLL_TEX,				//!< テキスト画像のTexture

	};

	/**VertexID*/
	enum VERTEX_ID
	{
		RESULT_BG_VTX,				//!< 結果画像のVertex
		RESULT_TEXT_VTX,			//!< 結果テキスト画像のVertex
		END_ROLL_VTX,				//!< テキスト画像のVertex
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
	D3DXVECTOR2			m_BackgroundPos;		//!< 結果背景の位置座標
	D3DXVECTOR2			m_TextPos;				//!< 結果テキストの位置座標
	D3DXVECTOR2			m_EndRollPos;			//!< エンドロールの位置座標
	float				m_ResultTextWidth;		//!< 結果テキストの横幅
	float				m_ResultTextHeight;		//!< 結果テキストの縦幅
	int					m_StartTimeCount;		//!< エンドロール開始時間をカウントする変数
	int					m_DispTimeCount;		//!< 表示時間をカウントする変数
	bool				m_IsFedeOutEnd;			//!< フェードアウト終了したかどうか		

};

#endif // END_ROLL_SCENE_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
