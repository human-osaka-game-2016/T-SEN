//==================================================================================================================================//
//!< @file		BattleDataManager.h
//!< @brief		BattleDataManagerクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef BATTLE_DATA_MANAGER_H
#define BATTLE_DATA_MANAGER_H

/**
* 戦闘に関するデータを管理するクラス
* Singletonパターン
*/
class BattleDataManager
{

public:

	/**
	* BattleDataManagerクラスのインスタンスを取得する関数
	* @return BattleDataManagerクラスのインスタンス
	*/
	static BattleDataManager& Instance()
	{
		static BattleDataManager battleDataManager;
		return battleDataManager;
	}

	/**
	* 初期化関数
	* @attention	この関数はBattleシーンのConstructor内で必ずよぶこと
	*/
	void			Initialize();

	/**ズームしたかどうかを確認する関数*/
	bool CheckZoom(){ return m_PlayerToZoom; }

	/**--Getter------------------------------------------------------------------------------------------*/

	inline int		GetPlayerHp(){ return m_PlayerHp; }
	inline float	GetPlayerSpeed(){ return m_PlayerSpeed; }
	inline int		GetMonsterHp(){ return m_MonsterHp; }
	inline int		GetMonsterHpMax(){ return m_MonsterHpMax; }
	inline int		GetMonsterCount(){ return m_MonsterCount;  }
	inline int		GetPlayerAttackDamage(){ return m_PlayerAttackedDamage; }
	inline int		GetBattleResult(){ return m_BattleResult; }

	/**--Setter------------------------------------------------------------------------------------------*/

	inline void		SetPlayerHp(int playerHp){ m_PlayerHp = playerHp; }
	inline void		SetPlayerSpeed(float playerSpeed){ m_PlayerSpeed = playerSpeed; }
	inline void		SetMonsterHp(int monsterHp){ m_MonsterHp = monsterHp; }
	inline void		SetMonsterHpMax(int monsterHpMax){ m_MonsterHpMax = monsterHpMax; }
	inline void		SetMonsterCount(int count){ m_MonsterCount = count; }
	inline void		SetPlayerAttackDamage(int playerDamage){ m_PlayerAttackedDamage = playerDamage; }
	inline void		SetBattleResult(bool result){ m_BattleResult = result; }
	inline void		SetPlayerToZoom(bool isZoom){ m_PlayerToZoom = isZoom; }

	/**Destructor*/
	~BattleDataManager(){}

private:
	int				m_PlayerHp;					//!< プレイヤー軍艦のHP
	float			m_PlayerSpeed;				//!< プレイヤー軍艦のスピード
	int				m_MonsterCount;				//!< モンスターの数をカウントする変数
	int				m_MonsterHp;				//!< モンスターのHP
	int				m_MonsterHpMax;				//!< モンスターのHP最大値
	int				m_PlayerAttackedDamage;		//!< プレイヤーが攻撃して与えたダメージ
	bool			m_BattleResult;				//!< 戦闘結果 trueが勝利、falseが敗北
	bool			m_PlayerToZoom;				//!< プレイヤーがズームしているかどうか

	/**Constructor*/
	BattleDataManager(){}

};

#endif	// BATTLE_DATA_MANAGER_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
