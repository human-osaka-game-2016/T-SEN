/**
* @file GameDataManager.h
* @brief GameDatamanagerクラスヘッダ
* @author haga
* @note 2016/11/03ファイル作成したが、実装はまだ行っていない
*/
#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

/**
* ゲームデータを管理するクラス
*/
class GameDataManager
{
public:
	GameDataManager();
	~GameDataManager();

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
		float m_Aggressivity[LVMAX];
		char m_Name[32];
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
		float m_Durability[LVMAX];
		char m_Name[32];
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
		float m_Speed[LVMAX];
		char m_Name[32];
	}ShipSpeed;

	void SetMoney(int money);  //お金のセッター関数
	int GetMoney();            //お金のゲッター関数
	ShipAggressivity* GetShipAggressivity();  //船の攻撃力の構造体のゲッター関数
	ShipDurability* GetShipDurability();      //船の耐久値の構造体のゲッター関数
	ShipSpeed* GetShipSpeed();                //船の機動力の構造体のゲッター関数
	void SetFightOffDays(int FightOffDays);
	int GetFightOffDays();                    //撃退日数のゲッター関数

private:
	int              m_Money;
	ShipAggressivity m_ShipAggressivity;  //船の攻撃力の構造体のメンバ変数
	ShipDurability   m_ShipDurability;    //船の耐久値の構造体のメンバ変数
	ShipSpeed        m_ShipSpeed;         //船の機動力の構造体のメンバ変数
	int m_FightOffDays;                   //撃退日数
};

#endif // GAMEDATA_MANAGER_H
