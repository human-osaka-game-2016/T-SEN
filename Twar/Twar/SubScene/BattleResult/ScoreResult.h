//==================================================================================================================================//
//!< @file		ScoreResult.h
//!< @brief		ScoreResultクラスヘッダ
//!< @auhtor	haga
//==================================================================================================================================//

#ifndef SCORE_RESULT_H
#define SCORE_RESULT_H

#include <d3dx9.h>

class GameDataManager;
class Font;

/**
* 戦闘結果のデータ(スコア)を表示するクラス
*/
class ScoreResult
{

public:
	/**
	* Constructor
	* @param pGameDatamanager	GameDataManagerのインスタンスへのポインタ
	*/
	explicit ScoreResult(GameDataManager* pGameDayaManagher);

	/**Destructor*/
	~ScoreResult();

	/**描画関数*/
	void Draw();

	/**取得した通貨のGetter*/
	inline int GetMoneyData(){ return m_Data[GETTEN_MONEY]; }

private:
	/**スコアの種類*/
	enum SCORE_LIST
	{
		PLAYER_DAMAGE_SCORE,	//!< プレイヤーが与えたダメージスコア
		ELAPSED_DAYS,			//!< 経過日数
		GETTEN_MONEY,			//!< 取得したお金
		LIST_MAX,				//!< スコアのリストの最大値
	};

	GameDataManager*	m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ
	int					m_Data[LIST_MAX];		//!< データ(数値)の静的配列
	Font*				m_pFont;				//!< Fontクラスのインスタンスへのポインタ

	/**データを初期化する関数*/
	void InitData();

	/**戦闘で取得した通貨の計算を行う関数*/
	int CalculateGettenMoney();
	
};

#endif // SCORE_RESULT_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
