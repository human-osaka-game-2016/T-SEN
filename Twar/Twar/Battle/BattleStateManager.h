/**
* @file		BattleStateManager.h
* @brief	BattleStateManagerクラスヘッダ
* @author	haga
* @todo		2016/12/08にファイルだけ作成。実装はあとで行う
*/

#ifndef BATTLE_STATE_MANAGER_H
#define BATTLE_STATE_MANAGER_H

#include "../Ship/ShipManager.h"

/**
* 戦闘シーンにおける状態(情報)を管理するクラス
*/
class BattleStateManager
{
public:

	static BattleStateManager& Instance()
	{
		static BattleStateManager dataManager;
		return dataManager;
	}
	
	void Init();

	void SetGameResult(bool isVictory);
	void SetMonsterHP(int monsterHp);
	void SetPlayerHP(int playerHp);
	void SetShipSpeed(float shipSpeed);
	void SetShipID(ShipManager::SHIP_ID    chosenShipID);
	void SetZoomFlag(bool isZoom);
	
	int GetMonsterHp(){ return m_MonsterHP; }
	int GetPlayerHp(){ return m_PlayerHP; }
	float GetShipSpeed(){ return m_ShipSpeed; }
	ShipManager::SHIP_ID GetShipID(){ return m_ChosenShipID; }

	bool CheckGameEnd(){ return m_IsEnd; }
	bool CheckResult(){ return m_IsVictory; }
	bool CheckZoom(){ return m_IsZoom; }

	~BattleStateManager();

private:
	int						m_MonsterHP;	// モンスターHP
	int						m_PlayerHP;		// プレイヤーHP
	float					m_ShipSpeed;	//  船のスピード
	ShipManager::SHIP_ID    m_ChosenShipID;
	bool					m_IsEnd;		// ゲーム終了かどうか
	bool					m_IsVictory;	// 勝利かどうか
	bool					m_IsZoom;

	BattleStateManager();
};

#endif	// BATTLE_STATE_MANAGER_H
