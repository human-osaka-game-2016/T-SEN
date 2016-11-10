#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include "Ship.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"

class ShipManager
{
	friend class Ship;

private:

//	enum SHIP_ID
//	{
//		BATTLESHIP,
//		CRUISER,
//		DESTROYER,
//
//		NONE,
//	};

	D3DXVECTOR3 templatePos[12];// =
//	{
//		{   0,   0,   0 },
//		{  10,   0,   0 },
//		{  20,   0,   0 },
//		{  30,   0,   0 },
//		{  40,   0,   0 },
//		{  50,   0,   0 },
//		{   0,   0, 100 },
//		{  10,   0, 100 },
//		{  20,   0, 100 },
//		{  30,   0, 100 },
//		{  40,   0, 100 },
//		{  50,   0, 100 }
//	};

	std::vector<Ship*> m_Army;
	std::vector<Ship*> m_Enemy;
	FbxRelated m_BattleShip;
	FbxRelated m_Cruiser;
	FbxRelated m_Destroyer;
	char m_ArmyCount;
	char m_EnemyCount;

public:

	enum SHIP_ID
	{
		BATTLESHIP,
		CRUISER,
		DESTROYER,

		NONE,
	};
	/*
	enum BATTLE_TYPE
	{
		PLAYERvsENEMY,
		PLAYERvsENEMYvsMONSTER,
		PLAYERandALLYvsMONSTER
	};
	*/

	D3DXVECTOR3 GetPlayerPos()
	{
		return m_Army[0]->m_ObjPos;
	}

	ShipManager();
	~ShipManager();
	void Control();
	void Draw();
	void Create(char* army, char* enemy, SHIP_ID* shipID);
};

#endif	//	SHIPMANAGER_H