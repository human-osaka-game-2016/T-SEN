//==================================================================================================================================//
//!< @file		BattleResult.h
//!< @brief		BattleResultクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef BATTLE_RESULT_H
#define BATTLE_RESULT_H

#include "../SubScene.h"

class ScoreResult;
class ResultBackground;
class GameMessage;
class GameDataManager;

namespace sub_scene
{

/**
* 戦闘結果表示シーンのクラス
*/
class BattleResult :public SubScene
{

public:
	/**TextureID*/
	enum TEXTURE_ID
	{
		RESULT_TEX,			//!< 結果画像のtexture
	};

	/**VertexID*/
	enum VERTEX_ID
	{
		RESULT_VTX,			//!< 結果画像のvertex
	};

	/**シーンの状態*/
	enum STATE
	{
		RESULT_FEDE_IN,					//!< 結果画像がフェードインしている状態  
		SCORE_DISP_RETURN_HOME,			//!< スコアが表示し、Homeへ移行する状態
		SCORE_DISP_RETURN_ENDROLL,		//!< スコアが表示し、EndRollSceneへ移行する状態
	};

	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	* @param pSaveDataManager SaveDataManagerクラスのインスタンスへのポインタ
	*/
	BattleResult(GameDataManager* pGameDataManager, GameTimer* pGameTimer, SaveDataManager* pSaveDataManager);

	/**デストラクタ*/
	virtual ~BattleResult();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();

private:
	ScoreResult*		m_pScoreResult;			//!< ScoreResultクラスのインスタンスへのポインタ
	ResultBackground*	m_pBackground;			//!< ResultBackgroundクラスのインスタンスへのポインタ
	GameMessage*		m_pMessage;				//!< GameMessageクラスのインスタンスへのポインタ
	STATE				m_State;				//!< シーンの状態を格納する変数
	int					m_SceneChangeTimeCount;	//!< シーンチェンジする時間をカウントする変数
	GameDataManager*    m_pGameDataManager;     //!< GameDataManagerクラスのインスタンスへのポインタ
};

}

#endif // BATTLE_RESULT_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//

