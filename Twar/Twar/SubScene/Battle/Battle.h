/**
* @file Battle.h
* @brief Battleクラスヘッダ
* @author haga
*/
#ifndef BATTLE_H
#define BATTLE_H

#include "../SubScene.h"

class Light;
class FieldManager;
class CameraController;
class LoadingThread;
class MonsterManager;
class ShipManager;
class CollisionManager;
class BattleUIManager;

namespace sub_scene
{

/**
* 戦闘シーンのクラス
*/
class Battle :public SubScene
{
public:
	/**TextureID*/
	enum TEXTURE_ID
	{
		EXPLOSION_TEX,		//!< 爆発画像
		LOAD_THREAD_TEX,		//!< ロード画面画像
		LIFE,					//!< ライフID
		LIFE_FLAME,			//!< 外装
		LIFE_DECORATION,		//!< 装飾
		ALIGNMENT,			//!< 照準器
		ALIGNMENTZOOM,		//!< ズーム
		UI,					//!< UI統合ファイル

	};

	/**VertexID*/
	enum VERTEX_ID
	{
		EXPLOSION_VTX,			//!< 爆発のVertex
		LOAD_THREAD_VTX,		//!< ロード画面のVertex
		METER,					//!< スピードメーター
		ALIGNMENT_VTX,
		AICON,					//!< スピードアイコン
		MONSTER_LIFE_GAUGE,		//!< 巨大生物体力ゲージ
		MONSTER_FLAME,			//!< 巨大生物体力フレーム
		MONSTER_BASE,			//!< 巨大生物体力ゲージの下地

	};

	/**
	* コンストラクタ
	* @param pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	* @param pGameTimer		  GameTimerクラスのインスタンスへのポインタ
	*/
	Battle(GameDataManager* pGameDataManager, GameTimer* pGameTimer);

	/**デストラクタ*/
	virtual ~Battle();

	/**コントロール関数*/
	virtual SUBSCENE_ID Control();

	/**描画関数*/
	virtual void Draw();
private:
	Light*                  m_pLight;					//!< ライト
	FieldManager*           m_pFieldManager;
	CameraController*       m_pCameraController;
	LoadingThread*			m_pLoadingThread;
	MonsterManager*         m_pMonsterManager;
	ShipManager*			m_pShipManager;
	CollisionManager*		m_pCollisionManager;
	BattleUIManager*		m_pBattleUIManager;
	BattleUIManager*		m_pUIManagaer;

	/**戦闘状態をチェックする*/
	bool CheckBattleState();

};

}

#endif // BATTLE_H
