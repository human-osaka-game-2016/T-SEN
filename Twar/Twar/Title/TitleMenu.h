/**
* @file		TitleMenu.h
* @brief	TitleMenuクラスヘッダ
* @author	haga
*/

#ifndef TITLE_MENU_H
#define TITLE_MENU_H

#include <vector>
#include "../Scene/TitleScene.h"

class MenuButton;
/**
* タイトルメニューの操作を管理するクラス.
*/
class TitleMenu
{
public:
	/**
	* コンストラクタ.
	* @param hasSaveData セーブデータがあるかどうか
	*/
	explicit TitleMenu(bool hasSaveData);

	~TitleMenu();

	/**コントロール関数*/
	TitleScene::STATE Control();

	/**描画関数*/
	void Draw();

private:
	TitleScene::STATE			m_MenuSelectState;		//!< メニューが選んでいるタイトルの状態
	std::vector<MenuButton>		m_MenuButton;			//!< メニューボタン

};

#endif	// TITLE_MENU_H
