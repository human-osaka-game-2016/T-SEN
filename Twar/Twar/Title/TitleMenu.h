/**
* @file		TitleMenu.h
* @brief	TitleMenuクラスヘッダ
* @author	haga
*/

#ifndef TITLE_MENU_H
#define TITLE_MENU_H

class MenuButton;
enum TITLE_STATE;

/**
* タイトルメニューの操作を管理するクラス.
*/
class TitleMenu
{
public:

	TitleMenu();

	~TitleMenu();

	TITLE_STATE Control();

	void Draw();

private:
	MenuButton*			m_pStartBtn;		//!< スタートボタン
	MenuButton*			m_pDataLoadBtn;		//!< データロードボタン
	bool				m_HasSaveData;		//!< セーブデータがあるかどうか

};

#endif	// TITLE_MENU_H
