//==================================================================================================================================//
//!< @file		GameDataManager.h
//!< @brief		GameDatamanagerクラスヘッダ
//!< @author	haga･matsuda
//==================================================================================================================================//

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

#include "../SubScene/SubScene.h"

/**
* ゲームデータを管理するクラス
*/
class GameDataManager
{

public:
	/**Constructor*/
	GameDataManager();

	/**Desutrctor*/
	~GameDataManager();

	/**船の艦種を識別するID*/
	enum SHIP_ID							
	{
		DESTROYER,		//!< 駆逐艦
		CRUISER,		//!< 巡洋艦
		BATTLESHIP,		//!< 戦艦
		SHIP_ID_MAX,
	};

	enum Level_ID
	{
		LV1,
		LV2,
		LV3,
		LV4,
		LV5,
		LV6,

		LV_MAX,
	};

	/**
	* ウェーブが終了したら呼び出す関数<br>
	* m_FightOffDaysを初期値にし、m_WaveCountを1つ加算する
	*/
	void ResetWaveData();

	/**--Getter--------------------------------------------------------------------------------------------------------------*/

	inline int							GetMoney(){ return m_Money; }										
	inline int			                GetShipAggressivity(int ShipID, int LvID){ return m_ShipAggressivity[ShipID][LvID]; }
	inline int                			GetShipDurability(int ShipID, int LvID){ return m_ShipDurability[ShipID][LvID]; }
	inline int			                GetShipSpeed(int ShipID, int LvID){ return m_ShipSpeed[ShipID][LvID]; }
	inline int							GetFightOffDays(){ return m_FightOffDays;  }
	inline int							GetWaveCount(){ return m_WaveCount; }
	inline bool                         GetBattleShipSelect(){ return m_IsBattleShipSelected; }
	inline bool                         GetCruiserSelect(){ return m_IsCruiserSelected; }
	inline GameDataManager::SHIP_ID		GetSelectedShipID(){ return m_SelectedShipID; }


	/**--Setter--------------------------------------------------------------------------------------------------------------*/

	inline void							SetMoney(int money){ m_Money = money; }
	inline void							SetFightOffDays(int fightOffDays){ m_FightOffDays = fightOffDays; }
	inline void							SetWaveCount(int waveCount){ m_WaveCount = waveCount; }
	inline void							SetSelectedShipID(GameDataManager::SHIP_ID id){ m_SelectedShipID = id; }
	inline void                         SetDestroyerAggressivity(int ShipAggressivity,int Lv){ m_ShipAggressivity[DESTROYER][Lv] = ShipAggressivity; }
	inline void                         SetBattleShipSelect(bool IsBattleShipSelected){ m_IsBattleShipSelected = IsBattleShipSelected; }
	inline void                         SetCruiserSelect(bool IsCuriserSelected){ m_IsCruiserSelected = IsCuriserSelected; }
private:
	int								m_Money;			 //!< プレイヤーの所持金
	int				                m_ShipAggressivity[SHIP_ID_MAX][LV_MAX];  //!< 船の攻撃力のメンバ変数
	int         					m_ShipDurability[SHIP_ID_MAX][LV_MAX];    //!< 船の耐久値のメンバ変数
	int						        m_ShipSpeed[SHIP_ID_MAX][LV_MAX];         //!< 船の機動力のメンバ変数
	int								m_FightOffDays;      //!< 撃退日数
	int								m_WaveCount;		 //!< ウェーブ数
	GameDataManager::SHIP_ID		m_SelectedShipID;	 //!< プレイヤーが選んだ船のID
	bool                            m_IsBattleShipSelected;
	bool                            m_IsCruiserSelected;

};

#endif // GAMEDATA_MANAGER_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//

