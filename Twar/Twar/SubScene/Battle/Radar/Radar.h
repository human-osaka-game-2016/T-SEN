/**
* @file		Radar.h
* @brief	Radarクラスヘッダ
* @author	haga
* @todo		2017/01/07 まだBattleDataManagerができていないので仮実装
*/

#ifndef RADAR_H
#define RADAR_H

#include "vector"
#include "d3dx9.h"

/**
* バトルにおけるオブジェクトの位置を把握しているクラス
*/
class Radar
{

public:
	/**
	* 実体を取得する関数.
	* Singletonパターン
	* @return  Raderの実体
	*/
	static Radar& Instance()
	{
		static Radar radar;
		return radar;
	}

	/**
	* 基点となる座標から1番近い船の座標をかえしてくれる関数
	* @param rPos	基点となる座標
	* @return		基点となる座標から1番近い船の座標
	*/
	D3DXVECTOR3 GetNearShipPos(const D3DXVECTOR3& rPos);

	/**
	* モンスターの座標をかえしてくれる関数
	* @return		モンスターの座標
	*/
	const D3DXVECTOR3& GetMonsterPos(){ return m_MonsterPos; };

	/**
	* AIが攻撃すべきターゲットの座標をかえしてくれる関数
	* @param rPos 自分の座標
	* @param playerAttackedCount プレイヤーに攻撃された回数
	*/
	D3DXVECTOR3 GetAIAttackTargetPos(const D3DXVECTOR3& rPos, int playerAttackedCount);

	/**
	* 船の座標をセットする関数
	* @param	rPos		セットしたい船の座標
	* @todo		この関数はBattleDataManagerの実装によって実装を変える予定
	*/
	void SetShipPos(const D3DXVECTOR3& rPos);

	/**
	* モンスターの座標をセットする関数
	* @param	rPos		セットしたいモンスターの座標
	* @todo		この関数はBattleDataManagerの実装によって実装を変える予定
	*/
	void SetMonsterPos(const D3DXVECTOR3& rPos);

	/**データをクリアにする関数*/
	void ClearData();

	/**デストラクタ*/
	~Radar();

private:

	/**比較用のデータ構造体*/
	struct ComparisionData
	{
		D3DXVECTOR3 pos;		//!< 座標
		float		length;		//!< 比較用
	};

	std::vector<D3DXVECTOR3>	m_ShipPos;				//!< 船の座標を格納する動的配列
	D3DXVECTOR3					m_MonsterPos;			//!< Monsterの座標を格納する動的配列

	/**
	* コンストラクタ.
	* Singletonpターンなのでprivate
	*/
	Radar();

	/**ソート用の関数*/
	static bool CompareLength(const ComparisionData& rLeft, const ComparisionData& rRight);

};

#endif	// RADAR_H
