/**
* @file		ScoreResult.h
* @brief	ScoreResultクラスヘッダ
* @auhtor	haga
*/

#ifndef SCORE_RESULT_H
#define SCORE_RESULT_H

#include <d3dx9.h>

class GameDataManager;
class Font;

/**
* 戦闘結果のデータ(スコア)を表示するクラス
* @todo データに関してはまだ決まっていない部分があるので、決まり次第再実装
*/
class ScoreResult
{

public:
	/**
	* コンストラクタ
	* @param pGameDatamanager	GameDataManagerのインスタンスへのポインタ
	*/
	explicit ScoreResult(GameDataManager* pGameDayaManagher);

	/**デストラクタ*/
	~ScoreResult();

	/**描画関数*/
	void Draw();
	
private:
	/**データの種類*/
	/**@todo 仮で決めている*/
	enum SCORE_LIST
	{
		BATTLE_SCORE,	//!< 戦闘スコア(仮)
		BATTLE_TIME,	//!< 戦闘時間
		LIST_MAX,		//!< スコアのリストの最大値
	};

	int				m_Data[LIST_MAX];		//!< データ(数値)の静的配列
	Font*			m_pFont;				//!< Fontクラスのインスタンスへのポインタ

	/**メンバーのDataを初期化する並列*/
	void InitData(GameDataManager* pGameDayaManagher);

};

#endif // SCORE_RESULT_H
