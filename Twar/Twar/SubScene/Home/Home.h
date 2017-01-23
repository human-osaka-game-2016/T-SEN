/**
* @file		Home.h
* @brief	Homeクラスヘッダ
* @author	haga
*/
#ifndef HOME_H
#define HOME_H

#include "../SubScene.h"

class HomeBackground;
class HomeMenu;

namespace sub_scene
{

/**
* 鎮守府シーンのクラス
*/
class Home :public SubScene
{
public:
	/**ホームの状態*/
	enum STATE
	{
		BATTLE_START,			//!< バトルから編成に変わる可能性はあり
		WORLD_MAP_START,		//!< 世界地図へ移行
		SHIPYARD_START,			//!< 造船所へ移行
		NOMAL,					//!< 通常状態
	};

	/**テクスチャーID*/
	enum TEXTRE_ID
	{
		BACKGROUND_TEX,			//!< 背景テクスチャ
		MENU_BTN_TEX,			//!< ホームのメニューボタンのテクスチャ
	};

	/*バーテックスID**/
	enum VERTEX_ID
	{
		BACKGROUND_VTX,			//!< 背景のバーテックス情報
		BATTLE_START_BTN_VTX,	//!< 出撃ボタンのバーテックス情報
	};

	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	* @param pSaveDataManager SaveDataManagerクラスのインスタンスへのポインタ
	*/
	Home(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	virtual ~Home();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	HomeBackground*		m_pBackground;			//!< HomeBackgroundクラスのインスタンスへのポインタ
	HomeMenu*			m_pHomeMenu;			//!< HomeMenuクラスのインスタンスへのポインタ
	Home::STATE			m_CurrentState;			//!< Homeの現在の状態

	/**
	* 初期化関数<br>
	* テクスチャー読み込みなどを行う
	*/
	void Init();

};

}

#endif // HOME_H
