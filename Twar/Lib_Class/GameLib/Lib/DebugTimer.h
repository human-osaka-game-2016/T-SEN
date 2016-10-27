/**
* @file   DebugTimer.h
* @brief   デバックの為の時間を計測するクラスのh
* @author haga
*/
#ifndef DEBUG_TIMER_H
#define DEBUG_TIMER_H

#include <iostream>
#include <vector>
#include "DebugFont.h"


/**
* デバック用タイマークラス<br>
* 時間取得にはtimeGetTimeを使用。他の時間取得関数も検討する
*/
class DebugTimer
{
private:
	/**計測時間管理用構造体*/
	struct DebugTime
	{
		std::string  timeName;					//!< 計測している時間
		DWORD		 time;						//!< 計測時間
		bool		 measureFlag;				//!< 計測しているかのフラグ
	};

	std::vector<DebugTime>	m_debugTime;		//!< 計測時間を管理する変数
	
public:
	/**コンストラクタ*/
	DebugTimer();

	/**デストラクタ*/
	~DebugTimer();

	/**
	* 計測する時間をセットする.
	* @param[in] timeName 計測する時間の名前
	*/
	void SetDebugTimer(std::string  timeName);

	/**
	* 時間計測をはじめる
	* @param[in] timeName 計測をはじめる時間の名前
	*/
	void StartTimer(std::string  timeName);

	/**
	* 時間計測終了
	* @param[in] timeName 計測を終える時間の名前
	*/
	void EndTimer(std::string  timeName);

	/**
	* 時間計測を再計測する
	* @param[in] timeName 再計測したい時間の名前
	*/
	void ReStart(std::string  timeName);

	/**
	* 時間計測結果を取得する
	* @param[in] timeName 計測結果を取得したい時間の名前
	*/
	DWORD GetResult(std::string  timeName);

	/**
	* 1つの計測結果だけ描画する
	* @param[in] timeName 結果を表示したい計測時間の名前
	* @param[in] pos 表示する座標
	*/
	void DrawResult(std::string  timeName, D3DXVECTOR2 pos);

	/**
	* 合計結果だけ描画する
	* @param[in] pos 表示する座標
	*/
	void DrawSumResult(D3DXVECTOR2 pos);

	/**
	* すべての計測結果と合計結果を描画する
	* @param[in] pos 表示開始座標
	*/
	void DrawAllResult(D3DXVECTOR2 pos);
};


#endif // DEBUG_TIMER_H
