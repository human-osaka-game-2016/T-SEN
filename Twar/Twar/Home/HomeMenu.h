/**
* @file		HomeMenu.h
* @brief	HomeMenuクラスヘッダ
* @author	haga
*/

#ifndef HOME_MENU_H
#define HOME_MENU_H

#include <vector>
#include "../Subscene/Home.h"

class MenuButton;

class HomeMenu
{
public:

	/**コンストラクタ*/
	HomeMenu();

	/**デストラクタ*/
	~HomeMenu();

	/**
	* コントロール関数.
	* @return	Homeシーンの状態をかえす
	*/
	sub_scene::Home::STATE		Control();

	/**描画関数*/
	void	Draw();

private:
	sub_scene::Home::STATE		m_MenuSelectState;		//!< メニューが選んでいるHomeの状態
	std::vector<MenuButton>		m_MenuButton;			//!< メニューボタン

};

#endif // HOME_MENU_H
