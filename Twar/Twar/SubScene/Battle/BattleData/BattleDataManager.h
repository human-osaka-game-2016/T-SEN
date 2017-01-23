/**
* @file		BattleDataManager.h
* @brief	BattleDataManagerクラスヘッダ
* @author	haga
* @todo		2016/12/08にファイルだけ作成。実装はあとで行う
*/

#ifndef BATTLE_DATA_MANAGER_H
#define BATTLE_DATA_MANAGER_H

/**
* 戦闘に関するデータを管理するクラス
*/
class BattleDataManager
{
public:
	static BattleDataManager& Instance()
	{
		static BattleDataManager dataManager;
		return dataManager;
	}
	~BattleDataManager();
	void SetPlayerHp(int hp);
	void SetPlayerSpeed(float speed);
	int GetPlayerHp();
	float GetPlayerSpeed();

private:
	BattleDataManager();

	int m_PlayerHp;
	float m_PlayerSpeed;
};


#endif	// BATTLE_DATA_MANAGER_H
