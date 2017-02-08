/**
* @file		Monster.h
* @brief	Monsterクラスヘッダ
* @author	haga
*/

#ifndef MONSTER_H
#define MONSTER_H

#include <d3dx9.h>
#include <vector>

class FbxModel;
class MonsterBulletManager;

/***
* 敵であるモンスターのクラス
*/
class Monster
{

public:
	/**
	* コンストラクタ
	* @param pModel				FbxModelクラスのインスタンスへのポインタ
	* @param pBulletManager		MonsterBulletManagerクラスのインスタンスへのポインタ
	*/
	Monster(FbxModel* pModel, MonsterBulletManager* pBulletManager);

	/**デストラクタ*/
	~Monster();

	/**
	* コントロール関数
	* @return 消滅したかどうか
	*/
	bool Control();

	/**描画関数*/
	void Draw();

private:

	/***ステータス(仮置き)*/
	struct STATUS
	{
		int Hp;				//!< HP
		int Power;			//!< 攻撃力
		int AttackInteval;	//!< 攻撃間隔
	};

	/**状態*/
	enum STATE
	{
		STANDBY,			//!< 待機
		ROTATION,			//!< 回転
		COMBAT,				//!< 戦闘
		MOVING,				//!< 移動
		DEATH,				//!< 死亡
	};

	D3DXVECTOR3						m_Pos;						//!< 位置座標
	D3DXMATRIX						m_MatWorld;					//!< ワールド変換行列
	float							m_Angle;					//!< 角度(向く方向)
	float							m_Radian;					//!< ラジアンを格納する変数
	float							m_BulletRadian;				//!< 弾のラジアンを格納
	FbxModel*						m_pModel;					//!< モデルデータ
	Monster::STATUS					m_Status;					//!< ステータス
	Monster::STATE					m_State;					//!< モンスターの状態
	float							m_SearchRange;				//!< 索敵範囲
	float							m_RollingSpeed;				//!< 回転速度
	D3DXVECTOR3						m_TargetPos;				//!< 攻撃対象の位置情報
	float							m_TargetRadian;				//!< 攻撃対象へのラジアン
	float							m_RadianDifference;			//!< モンスターとターゲットのラジアンの差
	int								m_AttackInterValCount;		//!< 攻撃間隔をカウント	
	int								m_NonAttackTimeCount;		//!< 攻撃していないときをカウント
	int								m_MoveTimeCount;			//!< 移動時間をカウント
	bool							m_HasMoved;					//!< 移動したかどうか
	bool							m_HasVanished;				//!< 消滅したかどうか
	MonsterBulletManager*			m_pBulletManager;			//!< MonsterBulletManagerクラスのインスタンスへのポインタ
	

	/**衝突を判断する関数*/
	void	JudgeColllision();

	/**索敵する関数*/
	void	SearchTarget();

	/**回転運動を行う関数*/
	void	Rotate();

	/**攻撃を行う関数*/
	void	AttackTarget();

	/**移動を行う関数*/
	void	Move();

	/**沈む行動を行う関数*/
	void	Fall();

	/**浮上する関数*/
	void	Rise();

	/**死んだ後消える動作関数*/
	void	FadeOut();

	/**姿勢制御関数*/
	void	ControlAttitude();

	/**
	* 平行移動関数.
	* @param x	x座標における移動量
	* @param y	y座標における移動量
	* @param z	z座標における移動量
	*/
	void MoveParallel(float x, float y, float z);

};

#endif	// MONSTER_H
