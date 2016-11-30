/**
* @file		MenuButton.h
* @brief	MenuButtonクラスヘッダ
* @author	haga
* @todo		2016/11/24ファイル作成のみ。実装は後で行う
*/

#ifndef MENU_BUTTON_H
#define	MENU_BUTTON_H

/**
* メニューボタンのクラス.
*/
class MenuButton
{
public:
	/**
	* コンストラクタ.
	* @param texID テクスチャーのID
	* @param vtxID バーテックスのID
	* @param width 横幅
	* @param height 縦幅
	*/
	MenuButton(int texID, int vtxID, float width, float height, D3DXVECTOR2 pos);

	~MenuButton();

	/**コントロール関数*/
	bool Control();

	/**描画関数*/
	void Draw();

	/**バーテックスのIDを返す*/
	int GetVtxID(){ return m_VtxID; }

private:
	int			m_TexID;
	int			m_VtxID;
	float		m_Width;
	float		m_Height;
	bool		m_HasCollided;
	D3DXVECTOR2 m_Pos;

	/**大きさを変える関数*/
	void Enlarge();

	/**サイズを元に戻す関数*/
	void Reinstate();

	/**マウスカーソルとあたっているかどうかを確認する*/
	void CheckCollisionCursor();

};

#endif	// MENU_BUTTON_H
