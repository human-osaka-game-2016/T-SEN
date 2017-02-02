//==================================================================================================================================//
//!< @file		Home.h
//!< @brief		Homeクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef HOME_H
#define HOME_H

#include <vector>
#include "../SubScene.h"

class HomeBackground;
class HomeMenu;
class GameWindow;

namespace sub_scene
{

/**
* 鎮守府シーンのクラス
*/
class Home :public SubScene
{
public:
	/**テクスチャーID*/
	enum TEXTRE_ID
	{
		BACKGROUND_TEX,			//!< 背景テクスチャ
		MENU_BTN_TEX,			//!< ホームのメニューのボタンテクスチャ
		HOME_TEX,				//!< ホーム関連のテクスチャ
	};

	/*VertexID**/
	enum VERTEX_ID
	{
		BACKGROUND_VTX,				//!< 背景
		BATTLE_START_BTN_VTX,		//!< 出撃ボタン
		POLITICS_BTN_VTX,			//!< 政略ボタン
		SHIP_INFO_WIN_VTX,			//!< 軍艦情報ウィンドウ
		SHIP_INFO_TEXT_VTX,			//!< 軍艦情報のテキスト
		TIME_LIMIT_WIN_3_VTX,		//!< 撃退期限表示ウィンドウ(残り三日)
		TIME_LIMIT_WIN_2_VTX,		//!< 撃退期限表示ウィンドウ(残り二日)
		TIME_LIMIT_WIN_1_VTX,		//!< 撃退期限表示ウィンドウ(残り一日)
		TENRYU_BTN_VTX,				//!< 天龍選択ボタン	
		MINEKAZE_BTN_VTX,			//!< 峯風選択ボタン
		KONGOU_BTN_VTX,				//!< 金剛選択ボタン
		SHIP_INFO_BG_TENRYU_VTX,	//!< 軍艦情報背景ウィンドウ(天龍)
		SHIP_INFO_BG_MINEKAZE_VTX,	//!< 軍艦情報背景ウィンドウ(峯風)
		SHIP_INFO_BG_KONGOU_VTX,	//!< 軍艦情報背景ウィンドウ(金剛)
		VTX_MAX,
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
	HomeBackground*					m_pBackground;			//!< HomeBackgroundクラスのインスタンスへのポインタ
	HomeMenu*						m_pHomeMenu;			//!< HomeMenuクラスのインスタンスへのポインタ
	std::vector<GameWindow*>		m_pGameWindows;			//!< GameWindowクラスのインスタンスへのポインタ

	/**
	* 初期化関数<br>
	* テクスチャー読み込みなどを行う
	*/
	void Init();

};

}

#endif // HOME_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
