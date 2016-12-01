/**
	@file ShipManager.h
	@brief ShipManagerクラスヘッダ
	@author kawaguchi
*/

#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include "Ship.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"

/**
	Ship管理クラス
*/
class ShipManager
{
	friend class Ship;

private:
	D3DXVECTOR3 m_TemplatePos[12];		//!<	自艦、味方艦、敵艦の初期位置	仮置き
	FbxRelated m_BattleShip;			//!<	戦艦のモデルデータ
	FbxRelated m_Cruiser;				//!<	巡洋艦のモデルデータ
	FbxRelated m_Destroyer;				//!<	駆逐艦のモデルデータ
	std::vector<Ship*> m_Army;			//!<	自艦＋味方艦の実体
	std::vector<Ship*> m_Enemy;			//!<	敵艦の実体
	char m_ArmyCount;					//!<	自艦＋味方艦の数
	char m_EnemyCount;					//!<	敵艦の数

public:

	enum SHIP_ID						//!<	船の艦種を識別するID
	{
		BATTLESHIP,
		CRUISER,
		DESTROYER,

		NONE,
	};

	/**
		ゲッター関数
	*/
	D3DXVECTOR3 GetPlayerPos(){ return m_Army[0]->m_ObjPos; }
	D3DXVECTOR3 GetCameraPos(){	return m_Army[0]->m_CameraPos; }
	D3DXVECTOR3 GetLookAtPos(){	return m_Army[0]->m_LookatPos; }
	float GetAngle(){ return m_Army[0]->m_Angle; }

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
	void CameraTransform(){ m_Army[0]->CameraTransWorld(100.f); }

};

#endif	//	SHIPMANAGER_H
