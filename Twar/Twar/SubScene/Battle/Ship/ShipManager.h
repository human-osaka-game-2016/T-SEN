/**
@file ShipManager.h
@brief ShipManagerクラスヘッダ
@author kawaguchi
*/

#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
//#include "Ship.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"

using namespace std;

class FbxRelated;
class BulletManager;
class Ship;

/**
Ship管理クラス
*/
class ShipManager
{
public:
	enum SHIP_ID						//!<	船の艦種を識別するID
	{
		BATTLESHIP,
		CRUISER,
		DESTROYER,

		NONE,
	};

	typedef struct SHIPSIZE
	{
		float m_MaxX, m_MaxY, m_MaxZ;
		float m_MinX, m_MinY, m_MinZ;
		float m_MaxR;
	}ShipSize;

private:
	friend class Ship;

	D3DXVECTOR3 m_TemplatePos[12];		//!<	自艦、味方艦、敵艦の初期位置	仮置き
	FbxRelated* m_BattleShip;			//!<	戦艦のモデルデータ
	ShipSize m_BattleShipSize;
	FbxRelated* m_Cruiser;				//!<	巡洋艦のモデルデータ
	ShipSize m_CruiserSize;
	FbxRelated* m_Destroyer;			//!<	駆逐艦のモデルデータ
	ShipSize m_DestroyerSize;
	BulletManager* m_pBulletManager;
	std::vector<Ship*> m_Army;			//!<	自艦＋味方艦の実体
	std::vector<Ship*> m_Enemy;			//!<	敵艦の実体
	char m_ArmyCount;					//!<	自艦＋味方艦の数
	char m_EnemyCount;					//!<	敵艦の数

public:

	/**
	ゲッター関数
	*/
	BulletManager* GetBulletManager(){ return m_pBulletManager; }
	ShipSize GetBattleShipSize(){ return m_BattleShipSize; }
	ShipSize GetCruiserSize(){ return m_CruiserSize; }
	ShipSize GetDestroyerSize(){ return m_DestroyerSize; }
	D3DXVECTOR3 GetPlayerPos(){ return m_Army[0]->m_ObjPos; }
	D3DXVECTOR3 GetCameraPos(){ return m_Army[0]->m_CameraPos; }
	D3DXVECTOR3 GetLookAtPos(){ return m_Army[0]->m_LookatPos; }
	float GetAngle(){ return m_Army[0]->m_Angle; }
	float GetArmyRotate(int i){ return m_Army[i]->m_Rotate; }
	float GetEnemyRotate(int i){ return m_Enemy[i]->m_Rotate; }
	float GetCameraRotate(){ return m_Army[0]->m_CameraRotate; }
	char GetArmyCount(){ return m_ArmyCount; }
	char GetEnemyCount(){ return m_EnemyCount; }
	D3DXVECTOR3 GetArmyObjPos(int i){ return m_Army[i]->m_ObjPos; }
	D3DXVECTOR3 GetEnemyObjPos(int i){ return m_Enemy[i]->m_ObjPos; }
	int GetArmyShipID(int i){ return m_Army[i]->m_ShipID; }
	int GetEnemyShipID(int i){ return m_Enemy[i]->m_ShipID; }

	/**
	セッター関数
	*/
	void SetArmyIsHit(int i, bool is){ m_Army[i]->m_IsHit = is; }
	void SetEnemyIsHit(int i, bool is){ m_Enemy[i]->m_IsHit = is; }
	void SetArmyIsRush(int i, bool is){ m_Army[i]->m_IsRush = is; }
	void SetEnemyIsRush(int i, bool is){ m_Enemy[i]->m_IsRush = is; }
	/**	コンストラクタ */
	ShipManager();

	/**	デストラクタ */
	~ShipManager();

	/**	コントロール関数 */
	void Control();

	/**	描画関数 */
	void Draw();

	/**
	Ship生成関数
	@param	army		自艦＋味方艦の数
	@param	enemy		敵艦の数
	@param	shipID		[１～６自＋味方、７～１２敵]からなる艦種識別IDの配列
	*/
	void Create(char* army, char* enemy, SHIP_ID* shipID);

	/**	カメラ位置を決める関数 */
	void CameraTransform(){ m_Army[0]->CameraTransWorld(); }/////////////////////////////////////////　もとは200　//////////////////////////////////////////////////

	bool IsDamageArmy(int i)
	{ 
		m_Army[i]->m_Status.m_Hp--; 
		if (m_Army[i]->m_Status.m_Hp <= 0)
		{
			return false;
		}
		return true;
	}
	
	bool IsDamageEnemy(int i)
		{
			m_Enemy[i]->m_Status.m_Hp--;
			if (m_Enemy[i]->m_Status.m_Hp <= 0)
			{
				return false;
			}
			return true;
		}
};

#endif	//	SHIPMANAGER_H
