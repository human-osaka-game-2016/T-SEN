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
	MenuButton();

	~MenuButton();

	void SetButtonData(int texID,int vtxID,float width,float height);

	void Enlarge(float width,float height);

	void Reinstate();

	void Draw();

private:
	int		m_TexID;
	int		m_VtxID;
	float	m_Width;
	float	m_Height;
};

#endif	// MENU_BUTTON_H
