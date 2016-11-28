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
	MenuButton(int texID, int vtxID, float width, float height);

	~MenuButton();

	void Enlarge(float width,float height);

	void Reinstate();

	/**
	* 描画関数.
	* @param posX x座標
	* @param posY y座標
	*/
	void Draw(float posX,float posY);

private:
	int		m_TexID;
	int		m_VtxID;
	float	m_Width;
	float	m_Height;
};

#endif	// MENU_BUTTON_H
