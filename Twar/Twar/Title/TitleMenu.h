/**
* @file		TitleMenu.h
* @brief	TitleMenuクラスヘッダ
* @author	haga
*/

#ifndef TITLE_MENU_H
#define TITLE_MENU_H

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
	TitleMenu(bool hasSaveData);

	~TitleMenu();

	/**コントロール関数*/
	TitleScene::STATE Control();

	/**描画関数*/
	void Draw();

	/*現在メニューが選んでいるボタンを判定する関数*/
	TitleScene::STATE SelectButton();

private:
	TitleScene::STATE	m_MenuSelectState;		//!< メニューが選んでいるタイトルの状態
	MenuButton*			m_pStartButton;			//!< スタートボタン
	MenuButton*			m_pDataLoadButton;		//!< データロードボタン
	bool				m_HasSaveData;			//!< セーブデータがあるかどうか

};

#endif	// TITLE_MENU_H
