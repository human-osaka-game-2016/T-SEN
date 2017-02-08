//==================================================================================================================================//
//!< @file		GameDataManager.h
//!< @brief		GameDatamanagerクラスヘッダ
//!< @author	haga･matsuda
//==================================================================================================================================//

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

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

	/*船の攻撃力の構造体*/
	typedef struct
	{
		enum Level
		{
			LV1 = 1,
			LV2,
			LV3,
			LV4,
			LV5,
			LVMAX,
		};
		float	m_Aggressivity[LVMAX];
		char	m_Name[32];

	}ShipAggressivity;

	/*船の耐久値の構造体*/
	typedef struct
	{
		enum Level
		{
			LV1 = 1,
			LV2,
			LV3,
			LV4,
			LV5,
			LVMAX,
		};
		float	m_Durability[LVMAX];
		char	m_Name[32];

	}ShipDurability;
	
	/*船の機動力の構造体*/
	typedef struct
	{
		enum Level
		{
			LV1 = 1,
			LV2,
			LV3,
			LV4,
			LV5,
			LVMAX,
		};
		float	m_Speed[LVMAX];
		char	m_Name[32];

	}ShipSpeed;

	/**
	* ウェーブが終了したら呼び出す関数<br>
	* m_FightOffDaysを初期値にし、m_WaveCountを1つ加算する
	*/
	void ResetWaveData();

	/**--Getter--------------------------------------------------------------------------------------------------------------*/

	inline int							GetMoney(){ return m_Money; }										
	inline ShipAggressivity*			GetShipAggressivity(){ return &m_ShipAggressivity; }
	inline ShipDurability*				GetShipDurability(){ return &m_ShipDurability; }
	inline ShipSpeed*					GetShipSpeed(){ return &m_ShipSpeed; }
	inline int							GetFightOffDays(){ return m_FightOffDays;  }
	inline int							GetWaveCount(){ return m_WaveCount; }
	inline GameDataManager::SHIP_ID		GetSelectedShipID(){ return m_SelectedShipID; }

	/**--Setter--------------------------------------------------------------------------------------------------------------*/

	inline void							SetMoney(int money){ m_Money = money; }
	inline void							SetFightOffDays(int fightOffDays){ m_FightOffDays = fightOffDays; }
	inline void							SetWaveCount(int waveCount){ m_WaveCount = waveCount; }
	inline void							SetSelectedShipID(GameDataManager::SHIP_ID id){ m_SelectedShipID = id; }
private:
	int								m_Money;			 //!< プレイヤーの所持金
	ShipAggressivity				m_ShipAggressivity;  //!< 船の攻撃力の構造体のメンバ変数
	ShipDurability					m_ShipDurability;    //!< 船の耐久値の構造体のメンバ変数
	ShipSpeed						m_ShipSpeed;         //!< 船の機動力の構造体のメンバ変数
	int								m_FightOffDays;      //!< 撃退日数
	int								m_WaveCount;		 //!< ウェーブ数
	GameDataManager::SHIP_ID		m_SelectedShipID;	 //!< プレイヤーが選んだ船のID

};

#endif // GAMEDATA_MANAGER_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//

