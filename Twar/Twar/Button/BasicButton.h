//=============================================================================================================================//
//!< @file		BasicButton.h
//!< @brief		BasicButtonクラスヘッダ
//!< @author	haga
//=============================================================================================================================//

#ifndef BASIC_BUTTON_H
#define BASIC_BUTTON_H

#include <d3dx9.h>
#include "Button.h"

/**
* 描画とマウスカーソルチェックを行うボタンクラス
*/
class BasicButton : public Button
{

public:
	/**
	* Constructor
	* @param rPos	位置座標
	* @param texID	TextureID
	* @param vtxID	VertexID
	* @param width	ボタンの横幅
	* @param height ボタンの縦幅
	*/
	BasicButton(const D3DXVECTOR2& rPos, int texID, int vtxID, float width, float height);

	/**Destructor*/
	virtual ~BasicButton();

	/**
	* コントロール関数
	* @return マウスカーソルがあたっているかどうか
	*/
	virtual bool Control()override;

	/**描画関数*/
	virtual void Draw()override;

	/**
	* VertexIDを取得する関数
	* @return VertexID
	*/
	virtual int GetVtxID()override{ return m_VtxID;  };

	/**
	* ボタンの横幅を取得する関数
	* @return ボタンの横幅
	*/
	virtual float GetButtonWidth()override{ return m_Width; };

	/**
	* ボタンの縦幅を取得する関数
	* @return ボタンの縦幅
	*/
	virtual float GetButtonHeight()override{ return m_Height; };

private:
	D3DXVECTOR2		m_Pos;				//!< 位置座標
	int				m_TexID;			//!< TextureID
	int				m_VtxID;			//!< VeretexID
	float			m_Width;			//!< ボタンの横幅
	float			m_Height;			//!< ボタンの縦幅

	/**
	* マウスカーソルとあたっているかどうかを確認する関数
	* @return 結果
	*/
	bool CheckCollisionMouseCursor();

};

#endif	// BASIC_BUTTON_H

//============================================================================================================================//
//END OF FILE
//============================================================================================================================//
